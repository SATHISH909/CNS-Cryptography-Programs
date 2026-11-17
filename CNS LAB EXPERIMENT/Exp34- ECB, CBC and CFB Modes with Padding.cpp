
#include <stdio.h>
#include <string.h>

#define MAX 256

/* Reversible 8-bit demonstration cipher */
unsigned char encryptByte(unsigned char x, unsigned char key) {
    return (unsigned char)(5 * x + key);
}

unsigned char decryptByte(unsigned char x, unsigned char key) {
    return (unsigned char)(205 * (x - key));
}

/* Add 0x80 followed by zero bytes */
int addPadding(unsigned char data[], int len) {
    int padded = ((len / 8) + 1) * 8;

    data[len] = 0x80;

    while (len < padded - 1) {
        len++;
        data[len] = 0;
    }

    return padded;
}

int removePadding(unsigned char data[], int len) {
    int i = len - 1;

    while (i >= 0 && data[i] == 0)
        i--;

    if (i >= 0 && data[i] == 0x80)
        return i;

    return len;
}

void printData(char label[], unsigned char data[], int len) {
    int i;

    printf("%s", label);
    for (i = 0; i < len; i++)
        printf("%02X ", data[i]);

    printf("\n");
}

int main() {
    unsigned char plain[MAX], padded[MAX];
    unsigned char ecb[MAX], cbc[MAX], cfb[MAX];
    unsigned char dec[MAX];
    unsigned char key, iv;
    int len, n, i;
    unsigned char previous;

    printf("ECB, CBC AND CFB MODE DEMONSTRATION\n");
    printf("-----------------------------------\n");

    printf("Enter plaintext: ");
    fgets((char *)plain, MAX, stdin);

    len = (int)strlen((char *)plain);

    if (len > 0 && plain[len - 1] == '\n')
        len--;

    if (len == 0 || len > 240) {
        printf("Enter plaintext containing 1 to 240 characters.\n");
        return 1;
    }

    printf("Enter 8-bit key (0-255): ");
    scanf("%hhu", &key);

    printf("Enter 8-bit IV (0-255): ");
    scanf("%hhu", &iv);

    memcpy(padded, plain, len);
    n = addPadding(padded, len);

    printData("\nPadded plaintext: ", padded, n);

    /* ECB Encryption */
    for (i = 0; i < n; i++)
        ecb[i] = encryptByte(padded[i], key);

    /* CBC Encryption */
    previous = iv;

    for (i = 0; i < n; i++) {
        cbc[i] = encryptByte(padded[i] ^ previous, key);
        previous = cbc[i];
    }

    /* CFB Encryption: 8-bit segments */
    previous = iv;

    for (i = 0; i < n; i++) {
        cfb[i] = padded[i] ^ encryptByte(previous, key);
        previous = cfb[i];
    }

    printf("\nENCRYPTION RESULTS\n");
    printData("ECB: ", ecb, n);
    printData("CBC: ", cbc, n);
    printData("CFB: ", cfb, n);

    /* ECB Decryption */
    for (i = 0; i < n; i++)
        dec[i] = decryptByte(ecb[i], key);

    printf("\nECB Decrypted: ");
    dec[removePadding(dec, n)] = '\0';
    printf("%s\n", dec);

    /* CBC Decryption */
    previous = iv;

    for (i = 0; i < n; i++) {
        unsigned char current = cbc[i];
        dec[i] = decryptByte(cbc[i], key) ^ previous;
        previous = current;
    }

    printf("CBC Decrypted: ");
    dec[removePadding(dec, n)] = '\0';
    printf("%s\n", dec);

    /* CFB Decryption */
    previous = iv;

    for (i = 0; i < n; i++) {
        dec[i] = cfb[i] ^ encryptByte(previous, key);
        previous = cfb[i];
    }

    printf("CFB Decrypted: ");
    dec[removePadding(dec, n)] = '\0';
    printf("%s\n", dec);

    return 0;
}

