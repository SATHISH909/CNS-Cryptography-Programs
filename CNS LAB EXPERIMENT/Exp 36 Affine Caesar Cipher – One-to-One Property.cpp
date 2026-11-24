
#include <stdio.h>
#include <string.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a) {
    int i;

    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }

    return -1;
}

int main() {
    char plaintext[100], ciphertext[100];
    int a, b, i, inverse;

    printf("AFFINE CAESAR CIPHER\n");
    printf("--------------------\n");

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b: ");
    scanf("%d", &b);

    a = (a % 26 + 26) % 26;
    b = (b % 26 + 26) % 26;

    if (gcd(a, 26) != 1) {
        printf("\nInvalid key!\n");
        printf("GCD(%d, 26) = %d\n", a, gcd(a, 26));
        printf("Encryption is not one-to-one.\n");

        printf("\nDemonstrating collision:\n");
        printf("For a = 2 and b = 3:\n");
        printf("E(0)  = %d\n", (2 * 0 + 3) % 26);
        printf("E(13) = %d\n", (2 * 13 + 3) % 26);

        printf("Both plaintext values produce the same ciphertext.\n");
        return 0;
    }

    printf("Enter plaintext: ");
    scanf("%99s", plaintext);

    inverse = modInverse(a);

    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];

        if (ch >= 'a' && ch <= 'z')
            ch = ch - 'a' + 'A';

        if (ch >= 'A' && ch <= 'Z') {
            int p = ch - 'A';
            int c = (a * p + b) % 26;
            ciphertext[i] = c + 'A';
        } else {
            ciphertext[i] = ch;
        }
    }

    ciphertext[i] = '\0';

    printf("\nEncrypted Text: %s\n", ciphertext);

    printf("Decrypted Text: ");

    for (i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];

        if (ch >= 'A' && ch <= 'Z') {
            int c = ch - 'A';
            int p = (inverse * (c - b + 26)) % 26;
            printf("%c", p + 'A');
        } else {
            printf("%c", ch);
        }
    }

    printf("\n");
    return 0;
}

