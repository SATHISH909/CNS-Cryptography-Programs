
#include <stdio.h>
#include <string.h>

long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp = exp / 2;
    }

    return result;
}

int main() {
    int e = 17, n = 3233;
    int table[26];
    char message[100];
    int i, value;

    printf("RSA Character-by-Character Attack\n");
    printf("---------------------------------\n");

    /* Build ciphertext lookup table */
    for (i = 0; i < 26; i++)
        table[i] = (int)powerMod(i, e, n);

    printf("Enter plaintext (A-Z only): ");
    scanf("%99s", message);

    printf("\nEncrypted characters:\n");

    for (i = 0; message[i] != '\0'; i++) {
        char ch = message[i];

        if (ch >= 'a' && ch <= 'z')
            ch = ch - 'a' + 'A';

        if (ch < 'A' || ch > 'Z') {
            printf("Only alphabetic characters are allowed.\n");
            return 0;
        }

        value = ch - 'A';
        printf("%c -> %d\n", ch, table[value]);
    }

    printf("\nAttacker's lookup-table decryption:\n");

    for (i = 0; message[i] != '\0'; i++) {
        char ch = message[i];

        if (ch >= 'a' && ch <= 'z')
            ch = ch - 'a' + 'A';

        value = ch - 'A';

        /* Attacker matches ciphertext against the table */
        printf("%c", 'A' + value);
    }

    printf("\n");
    return 0;
}

