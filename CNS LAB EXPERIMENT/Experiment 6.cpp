
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int modInverse(int a)
{
    for (int i = 1; i < 26; i++)
        if ((a * i) % 26 == 1)
            return i;
    return -1;
}

int main()
{
    char cipher[1000];
    int a, b, inv, i;
    char c;

    printf("Enter ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    // B is assumed to represent E
    // U is assumed to represent T
    int x = 'B' - 'A';
    int y = 'U' - 'A';
    int e = 'E' - 'A';
    int t = 'T' - 'A';

    // Solve a*x + b = y (mod 26)
    // using the assumed mappings B->E and U->T
    int found = 0;

    for (a = 1; a < 26; a++)
    {
        if (a % 2 == 0 || a % 13 == 0)
            continue;

        b = (e - a * x) % 26;
        if (b < 0) b += 26;

        if ((a * y + b) % 26 == t)
        {
            inv = modInverse(a);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No valid key found for these assumptions.\n");
        return 0;
    }

    printf("Affine key: a = %d, b = %d\n", a, b);
    printf("Decrypted text: ");

    for (i = 0; cipher[i] != '\0'; i++)
    {
        c = cipher[i];

        if (isupper((unsigned char)c))
            putchar(((inv * ((c - 'A' - b + 26) % 26)) % 26) + 'A');
        else if (islower((unsigned char)c))
            putchar(((inv * ((c - 'a' - b + 26) % 26)) % 26) + 'a');
        else
            putchar(c);
    }

    return 0;
}
