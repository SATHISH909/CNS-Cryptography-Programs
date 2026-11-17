
#include <stdio.h>
#include <string.h>

void generateSubkey(unsigned char L[], unsigned char K[],
                    int size, unsigned char R) {
    int i;
    int carry = 0, nextCarry;

    for (i = size - 1; i >= 0; i--) {
        nextCarry = (L[i] >> 7) & 1;
        K[i] = (unsigned char)((L[i] << 1) | carry);
        carry = nextCarry;
    }

    if (carry)
        K[size - 1] ^= R;
}

void printHex(unsigned char data[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%02X", data[i]);
    printf("\n");
}

int hexValue(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

int readHex(char str[], unsigned char data[], int size) {
    int i, h, l;

    if ((int)strlen(str) != size * 2)
        return 0;

    for (i = 0; i < size; i++) {
        h = hexValue(str[2 * i]);
        l = hexValue(str[2 * i + 1]);

        if (h < 0 || l < 0)
            return 0;

        data[i] = (unsigned char)(h * 16 + l);
    }

    return 1;
}

int main() {
    unsigned char L[16], K1[16], K2[16];
    char input[40];

    printf("CMAC Subkey Generation\n");
    printf("----------------------\n");

    /* 64-bit block */
    printf("\nEnter 64-bit L (16 hex digits): ");
    scanf("%39s", input);

    if (!readHex(input, L, 8)) {
        printf("Invalid 64-bit hexadecimal input.\n");
        return 1;
    }

    generateSubkey(L, K1, 8, 0x1B);
    generateSubkey(K1, K2, 8, 0x1B);

    printf("\n64-bit Block Results:\n");
    printf("L  = ");
    printHex(L, 8);
    printf("K1 = ");
    printHex(K1, 8);
    printf("K2 = ");
    printHex(K2, 8);

    /* 128-bit block */
    printf("\nEnter 128-bit L (32 hex digits): ");
    scanf("%39s", input);

    if (!readHex(input, L, 16)) {
        printf("Invalid 128-bit hexadecimal input.\n");
        return 1;
    }

    generateSubkey(L, K1, 16, 0x87);
    generateSubkey(K1, K2, 16, 0x87);

    printf("\n128-bit Block Results:\n");
    printf("L  = ");
    printHex(L, 16);
    printf("K1 = ");
    printHex(K1, 16);
    printf("K2 = ");
    printHex(K2, 16);

    return 0;
}

