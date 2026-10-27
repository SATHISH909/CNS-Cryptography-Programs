
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char plain[1000];
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cipher[] = "CIPHERABDFGJKLMNOQSTUVWXYZ";
    int i, j;
    char ch;

    printf("Enter plaintext: ");
    fgets(plain, sizeof(plain), stdin);

    printf("Encrypted text: ");

    for (i = 0; plain[i] != '\0'; i++)
    {
        ch = plain[i];

        if (isalpha((unsigned char)ch))
        {
            for (j = 0; j < 26; j++)
            {
                if (toupper((unsigned char)ch) == alphabet[j])
                {
                    putchar(cipher[j]);
                    break;
                }
            }
        }
        else
        {
            putchar(ch);
        }
    }

    return 0;
}
