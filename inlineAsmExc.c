#include <stdio.h>

void copyArr(int *, int *, int);
int findMax(int *, int);
void revArr(int *, int);
void cpArrATT(int *, int *, int);
int fMaxATT(int *, int);
void revArrATT(int *, int);

int main()
{
    int num1 = 12;
    int num2 = 8;

    int *num1ptr = &num1;
    int *num2ptr = &num2;

    int addedResult = 0;
    int minusResult = 0;

    int rotatedLResult;
    int rotatedRResult;

    int cLeadingZ;

    printf("Input values:\n");
    printf("num1 = %d\n", num1);
    printf("num2 = %d\n", num2);

    // Ex1: Addition and Subtraction
    __asm__ __volatile__(
        ".intel_syntax noprefix\n\t"
        "mov eax, %2\n\t"
        "add eax, %3\n\t"
        "mov %0, eax\n\t"
        "sub eax, %3\n\t" // here re-used the same register for the sub also
        "mov %1, eax\n\t"
        ".att_syntax prefix\n\t"
        : "+r"(addedResult), "=r"(minusResult) // here I was facing issue with two '=' operation and it was not showing the output
        // so I used +r and = operations.
        : "r"(num1), "r"(num2)
        : "eax");

    printf("\nAfter computation:\n");
    printf("Added result = %d\n", addedResult);
    printf("Subtracted result = %d\n", minusResult);

    // Ex2: Bitwise Operations
    // XOR swap (without XCHG instruction)
    __asm__ __volatile__(
        ".intel_syntax noprefix\n\t"
        "mov eax, [%0]\n\t" // Load %0 into eax
        "xor eax, [%1]\n\t" // eax = eax XOR %1
        "mov [%0], eax\n\t" // %0 = eax
        "mov ebx, [%1]\n\t" // Load %1 into ebx
        "xor ebx, [%0]\n\t" // ebx = ebx XOR %0 (updated value)
        "mov [%1], ebx\n\t" // %1 = ebx
        "mov eax, [%0]\n\t" // Load %0 into eax again
        "xor eax, [%1]\n\t" // eax = eax XOR %1 (updated value)
        "mov [%0], eax\n\t" // %0 = eax
        ".att_syntax prefix\n\t"
        :
        : "r"(num1ptr), "r"(num2ptr)
        : "eax", "ebx");

    printf("\nAfter swap:\n");
    printf("num1 = %d\n", num1);
    printf("num2 = %d\n", num2);

    // Bit rotation (Rotating left & left by Immediate constant value)
    __asm__ __volatile__(
        ".intel_syntax noprefix\n\t"
        "mov eax, %2\n\t"
        "rol eax, 2\n\t" // rotates left by 2
        "mov %0, eax\n\t"
        "ror eax, 2\n\t" // rotates right by 2
        "mov %1, eax\n\t"
        ".att_syntax prefix\n\t"
        : "+r"(rotatedLResult), "=r"(rotatedRResult)
        : "r"(num1)
        : "eax");

    printf("\nAfter rotation:\n");
    printf("num1 = %d\n", num1);
    printf("Rotated Left Result = %d\n", rotatedLResult);
    printf("Rotated Right Result = %d\n", rotatedRResult);

    // Count leading zeros
    __asm__ __volatile__(
        ".intel_syntax noprefix\n\t"
        "lzcnt %1, %0\n\t" // counts the number of consecutive zero bits, until the first 1 bit is found and stores value in cLeadingZ
        ".att_syntax prefix\n\t"
        : "=r"(cLeadingZ)
        : "r"(num1));

    printf("\nAfter counting leading zeros:\n");
    printf("num1 = %d\n", num1);
    printf("Count leading zeros Result = %d\n\n", cLeadingZ);

    // Ex3: Memory Operations
    // Ex 4: Mixed Syntax
    // Intel Syntax with ptrs
    // Cp
    int arr[] = {23, 12, 45, 20, 90, 89, 95, 32, 65, 19};
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[5] = {0};
    int len = 5;
    int arrLen = 10;
    copyArr(arr1, arr2, len);

    printf("Original array: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("Copied array: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n\n");

    // Max
    int max = findMax(arr, arrLen);
    printf("Array: ");
    for (int i = 0; i < arrLen; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Maximum value: %d\n\n", max);

    // Rev
    printf("=== Reversing Array In-Place ===\n");
    printf("Original array: ");
    for (int i = 0; i < arrLen; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    revArr(arr, arrLen);

    printf("Reversed array: ");
    for (int i = 0; i < arrLen; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // AT&T syntax with memory operands
    // Cp
    cpArrATT(arr1, arr2, len);

    printf("Original array: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("Copied array: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n\n");

    // Max
    int maxATT = fMaxATT(arr, arrLen);

    printf("Array: ");
    for (int i = 0; i < arrLen; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Maximum value: %d\n\n", maxATT);

    // Rev
    printf("=== Reverse Array (AT&T Syntax) ===\n");
    printf("Original array: ");
    for (int i = 0; i < arrLen; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    revArrATT(arr, arrLen);

    printf("Reversed array: ");
    for (int i = 0; i < arrLen; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    return 0;
}
// These three questions are done using poiters which covers the next Intel syntax with pointers
// Copy array elements using assembly
void copyArr(int *source, int *dest, int len)
{
    int *srcPtr = source;
    int *destPtr = dest;

    printf("=== Copying Array ===\n");
    __asm__ __volatile__(
        ".intel_syntax noprefix\n\t"
        "mov rdi, %0\n\t"  // rdi = source pointer
        "mov rsi, %1\n\t"  // rsi = destination pointer
        "mov ecx, %2\n\t"  // ecx = len
        "xor eax, eax\n\t" // eax = index (0)
        "copy_loop:\n\t"
        "cmp eax, ecx\n\t"           // Compare index with len
        "jge copy_done\n\t"          // If index >= len, done
        "mov ebx, [rdi + rax*4]\n\t" // Load source[index] into ebx
        "mov [rsi + rax*4], ebx\n\t" // Store to destination[index]
        "inc eax\n\t"                // index++
        "jmp copy_loop\n\t"
        "copy_done:\n\t"
        ".att_syntax prefix\n\t"
        :
        : "r"(srcPtr), "r"(destPtr), "r"(len)
        : "rax", "rbx", "rdi", "rsi", "rcx", "memory");
}

// Find maximum value in array
int findMax(int *arr, int len)
{
    int max = 0;
    int *arrPtr = arr;

    printf("=== Finding Maximum Value ===\n");
    __asm__ __volatile__(
        ".intel_syntax noprefix\n\t"
        "mov rdi, %1\n\t"    // rdi = array pointer
        "mov ecx, %2\n\t"    // ecx = len
        "mov eax, [rdi]\n\t" // eax = arr[0] (initial max)
        "mov ebx, 1\n\t"     // ebx = index (1)
        "max_loop:\n\t"
        "cmp ebx, ecx\n\t"           // Compare index with len
        "jge max_done\n\t"           // If index >= len, done
        "mov edx, [rdi + rbx*4]\n\t" // Load arr[index] into edx
        "cmp eax, edx\n\t"           // Compare max with arr[index]
        "cmovl eax, edx\n\t"         // If max < arr[index], update max
        "inc ebx\n\t"                // index++
        "jmp max_loop\n\t"
        "max_done:\n\t"
        "mov %0, eax\n\t" // Move result back to max
        ".att_syntax prefix\n\t"
        : "=r"(max)
        : "r"(arrPtr), "r"(len)
        : "rax", "rbx", "rcx", "rdx", "rdi", "cc");

    return max;
}

// Reverse an array in-place
void revArr(int *arr, int len)
{
    int *arrPtr = arr;

    __asm__ __volatile__(
        ".intel_syntax noprefix\n\t"
        "mov rdi, %0\n\t"  // rdi = array pointer
        "xor ecx, ecx\n\t" // ecx = left index (0)
        "mov eax, %1\n\t"  // eax = len
        "dec eax\n\t"      // eax = right index (len - 1)
        "reverse_loop:\n\t"
        "cmp ecx, eax\n\t"           // Compare left with right
        "jge reverse_done\n\t"       // If left >= right, done
        "mov ebx, [rdi + rcx*4]\n\t" // Load arr[left] into ebx
        "mov edx, [rdi + rax*4]\n\t" // Load arr[right] into edx
        "mov [rdi + rcx*4], edx\n\t" // Store arr[right] at arr[left]
        "mov [rdi + rax*4], ebx\n\t" // Store arr[left] at arr[right]
        "inc ecx\n\t"                // left++
        "dec eax\n\t"                // right--
        "jmp reverse_loop\n\t"
        "reverse_done:\n\t"
        ".att_syntax prefix\n\t"
        :
        : "r"(arrPtr), "r"(len)
        : "rax", "rbx", "rcx", "rdx", "rdi", "memory", "cc");
}

// Rwriting all the above functions using AT&T syntax with memory operands
// Copy array elements using assembly
void cpArrATT(int *source, int *dest, int len)
{
    printf("=== Copy Array (AT&T Syntax) ===\n");
    __asm__ __volatile__(
        "xorl %%ecx, %%ecx\n\t" // ecx = 0 (index)
        "copy_loop_att:\n\t"
        "cmpl %2, %%ecx\n\t"             // Compare index with len
        "jge copy_done_att\n\t"          // If index >= len, exit
        "movl (%0, %%rcx, 4), %%eax\n\t" // Load source[index] into eax
        "movl %%eax, (%1, %%rcx, 4)\n\t" // Store eax to dest[index]
        "incl %%ecx\n\t"                 // index++
        "jmp copy_loop_att\n\t"
        "copy_done_att:\n\t"
        :
        : "r"(source), "r"(dest), "m"(len)
        : "eax", "ecx", "memory");
}

// Find maximum value in array
int fMaxATT(int *arr, int len)
{
    int max = 0;
    printf("=== Find Maximum (AT&T Syntax) ===\n");
    __asm__ __volatile__(
        "movl $0, %%ecx\n\t"      // ecx = 0
        "movl (%%rdi), %%eax\n\t" // Load arr[0]
        "loop_start:\n\t"
        "incl %%ecx\n\t"                    // ecx++
        "cmpl %%esi, %%ecx\n\t"             // Compare ecx with len (in esi)
        "jge loop_end\n\t"                  // If ecx >= len, exit
        "movl (%%rdi, %%rcx, 4), %%ebx\n\t" // Load arr[ecx]
        "cmpl %%ebx, %%eax\n\t"             // Compare max vs arr[ecx]
        "cmovl %%ebx, %%eax\n\t"            // If less, update
        "jmp loop_start\n\t"
        "loop_end:\n\t"
        : "=a"(max)
        : "D"(arr), "S"(len) // Force RDI and RSI
        : "ebx", "ecx", "cc");
    return max;
}

// Reverse an array in-place
void revArrATT(int *arr, int len)
{
    __asm__ __volatile__(
        "xorl %%ecx, %%ecx\n\t" // ecx = 0 (left index)
        "movl %1, %%eax\n\t"    // eax = len
        "decl %%eax\n\t"        // eax = len - 1 (right index)
        "reverse_loop_att:\n\t"
        "cmpl %%eax, %%ecx\n\t"          // Compare left with right
        "jge reverse_done_att\n\t"       // If left >= right, exit
        "movl (%0, %%rcx, 4), %%ebx\n\t" // Load arr[left] into ebx
        "movl (%0, %%rax, 4), %%edx\n\t" // Load arr[right] into edx
        "movl %%edx, (%0, %%rcx, 4)\n\t" // Store arr[right] at arr[left]
        "movl %%ebx, (%0, %%rax, 4)\n\t" // Store arr[left] at arr[right]
        "incl %%ecx\n\t"                 // left++
        "decl %%eax\n\t"                 // right--
        "jmp reverse_loop_att\n\t"
        "reverse_done_att:\n\t"
        :
        : "r"(arr), "m"(len)
        : "eax", "ebx", "ecx", "edx", "memory", "cc");
}

/*
gcc -o program program.c

*/
