
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char plain[] = "SEND MORE MONEY";
    char target[] = "CASH NOT NEEDED";
    int key[] = {9, 0, 1, 7, 23, 15, 21,
                 14, 11, 11, 2, 8, 9};

    char cipher[100], decrypted[100];
    int i, j = 0;

    // Encryption
    for (i = 0; plain[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)plain[i]))
        {
            cipher[i] = ((toupper(plain[i]) - 'A'
                         + key[j]) % 26) + 'A';
            j++;
        }
        else
            cipher[i] = plain[i];
    }
    cipher[i] = '\0';

    printf("Original Plaintext : %s\n", plain);
    printf("Encrypted Ciphertext: %s\n", cipher);

    // Generate new key for target plaintext
    int newKey[13];

    j = 0;
    for (i = 0; cipher[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)cipher[i]))
        {
            newKey[j] = (cipher[i] - 'A'
                         - (target[i] - 'A') + 26) % 26;
            j++;
        }
    }

    // Decryption
    j = 0;
    for (i = 0; cipher[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)cipher[i]))
        {
            decrypted[i] = ((cipher[i] - 'A'
                            - newKey[j] + 26) % 26) + 'A';
            j++;
        }
        else
            decrypted[i] = cipher[i];
    }
    decrypted[i] = '\0';

    printf("Decrypted Plaintext : %s\n", decrypted);

    printf("\nNew Key Stream: ");
    for (i = 0; i < 13; i++)
        printf("%d ", newKey[i]);

    printf("\n");

    return 0;
}

