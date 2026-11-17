
#include <stdio.h>

/* Toy 8-bit block cipher for demonstration only */
unsigned char encrypt(unsigned char block, unsigned char key) {
    return (unsigned char)((5 * block + key) % 256);
}

int main() {
    unsigned char key, X, T;
    unsigned char secondBlock;
    unsigned char C1, C2;

    printf("CBC-MAC Forgery Demonstration\n");
    printf("-----------------------------\n");

    printf("Enter 8-bit key (0-255): ");
    scanf("%hhu", &key);

    printf("Enter one-block message X (0-255): ");
    scanf("%hhu", &X);

    /* MAC of the original one-block message */
    T = encrypt(X, key);

    printf("\nOriginal message X = %u (0x%02X)\n", X, X);
    printf("Original MAC T = %u (0x%02X)\n", T, T);

    /* Construct the forged second block */
    secondBlock = X ^ T;

    printf("\nForged two-block message:\n");
    printf("Block 1 = %u (0x%02X)\n", X, X);
    printf("Block 2 = X XOR T = %u (0x%02X)\n",
           secondBlock, secondBlock);

    /* CBC-MAC calculation */
    C1 = encrypt(X, key);
    C2 = encrypt(secondBlock ^ C1, key);

    printf("\nCBC-MAC calculation:\n");
    printf("First block MAC  = %u (0x%02X)\n", C1, C1);
    printf("Second block MAC = %u (0x%02X)\n", C2, C2);

    if (T == C2)
        printf("\nForgery successful: Both MAC values are equal.\n");
    else
        printf("\nMAC values are different.\n");

    return 0;
}

