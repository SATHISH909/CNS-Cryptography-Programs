
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int key[2][2] = {{9, 4}, {5, 7}};
    int inv[2][2] = {{5, 12}, {15, 25}};
    char text[200], cipher[200], decrypt[200];
    int i, j = 0, a, b, x, y;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i] != '\0'; i++)
        if (isalpha((unsigned char)text[i]))
            text[j++] = toupper((unsigned char)text[i]);

    if (j % 2 != 0)
        text[j++] = 'X';

    text[j] = '\0';

    // Encryption
    for (i = 0; i < j; i += 2)
    {
        a = text[i] - 'A';
        b = text[i + 1] - 'A';

        cipher[i] = (key[0][0] * a + key[0][1] * b) % 26 + 'A';
        cipher[i + 1] = (key[1][0] * a + key[1][1] * b) % 26 + 'A';
    }
    cipher[j] = '\0';

    printf("\nEncrypted text: %s\n", cipher);

    // Decryption
    for (i = 0; i < j; i += 2)
    {
        a = cipher[i] - 'A';
        b = cipher[i + 1] - 'A';

        x = (inv[0][0] * a + inv[0][1] * b) % 26;
        y = (inv[1][0] * a + inv[1][1] * b) % 26;

        decrypt[i] = x + 'A';
        decrypt[i + 1] = y + 'A';
    }
    decrypt[j] = '\0';

    printf("Decrypted text: %s\n", decrypt);

    return 0;
}

