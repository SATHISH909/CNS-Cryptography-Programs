
#include <stdio.h>
#include <string.h>

int main() {
    char plaintext[] = "sendmoremoney";
    char target[] = "cashnotneeded";
    char ciphertext[20];

    int key[13] = {
        9, 0, 1, 7, 23, 15, 21,
        14, 11, 11, 2, 8, 9
    };

    int newKey[13];
    int i;

    printf("VIGENERE ONE-TIME PAD\n");
    printf("---------------------\n");

    /* Encryption */
    for (i = 0; i < 13; i++) {
        int p = plaintext[i] - 'a';
        int c = (p + key[i]) % 26;
        ciphertext[i] = c + 'a';
    }

    ciphertext[13] = '\0';

    printf("Plaintext  : send more money\n");
    printf("Ciphertext : ");

    for (i = 0; i < 13; i++) {
        printf("%c", ciphertext[i]);

        if (i == 3 || i == 7)
            printf(" ");
    }

    printf("\n\nOriginal Key Stream:\n");

    for (i = 0; i < 13; i++)
        printf("%d ", key[i]);

    /* Find key for the second plaintext */
    for (i = 0; i < 13; i++) {
        int c = ciphertext[i] - 'a';
        int p = target[i] - 'a';

        newKey[i] = (c - p + 26) % 26;
    }

    printf("\n\nSecond Plaintext: cash not needed\n");

    printf("New Key Stream:\n");
    for (i = 0; i < 13; i++)
        printf("%d ", newKey[i]);

    printf("\n");

    return 0;
}

