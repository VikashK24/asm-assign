#include "inlineAsmExc.h"

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
