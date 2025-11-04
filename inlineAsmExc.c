#include "inlineAsmExc.h"

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
    addSub(addedResult, minusResult, num1, num2);

    printf("\nAfter computation:\n");
    printf("Added result = %d\n", addedResult);
    printf("Subtracted result = %d\n", minusResult);

    // Ex2: Bitwise Operations
    // XOR swap (without XCHG instruction)
    xorSwap(num1ptr, num2ptr);

    printf("\nAfter swap:\n");
    printf("num1 = %d\n", num1);
    printf("num2 = %d\n", num2);

    // Bit rotation (Rotating left & left by Immediate constant value)
    bitRotate(rotatedLResult, rotatedRResult, num1);

    printf("\nAfter rotation:\n");
    printf("num1 = %d\n", num1);
    printf("Rotated Left Result = %d\n", rotatedLResult);
    printf("Rotated Right Result = %d\n", rotatedRResult);

    // Count leading zeros
    countLeadingZeros(cLeadingZ, num1);

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
/*
gcc -o program program.c

*/
