#include "inlineAsmExc.h"

void addSub(int addedResult, int minusResult, int num1, int num2)
{
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
}

void xorSwap(int *num1ptr, int *num2ptr)
{
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
}

void bitRotate(int rotatedLResult, int rotatedRResult, int num1)
{
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
}
void countLeadingZeros(int cLeadingZ, int num1)
{
    __asm__ __volatile__(
        ".intel_syntax noprefix\n\t"
        "lzcnt %1, %0\n\t" // counts the number of consecutive zero bits, until the first 1 bit is found and stores value in cLeadingZ
        ".att_syntax prefix\n\t"
        : "=r"(cLeadingZ)
        : "r"(num1));
}