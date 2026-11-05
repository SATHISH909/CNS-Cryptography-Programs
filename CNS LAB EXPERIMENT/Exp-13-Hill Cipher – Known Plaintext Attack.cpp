
#include <stdio.h>
#include <string.h>

int mod(int n)
{
    return (n % 26 + 26) % 26;
}

int inverse(int n)
{
    for (int i = 1; i < 26; i++)
        if ((n * i) % 26 == 1)
            return i;
    return -1;
}

int main()
{
    char p[] = "HELP";
    char c[] = "HIAT";

    int P[2][2], C[2][2], K[2][2];
    int det, inv, i, j;

    // Convert plaintext and ciphertext into matrices
    for (i = 0; i < 2; i++)
    {
        P[0][i] = p[2 * i] - 'A';
        P[1][i] = p[2 * i + 1] - 'A';

        C[0][i] = c[2 * i] - 'A';
        C[1][i] = c[2 * i + 1] - 'A';
    }

    // Calculate determinant and inverse
    det = mod(P[0][0] * P[1][1] -
              P[0][1] * P[1][0]);

    inv = inverse(det);

    if (inv == -1)
    {
        printf("Key cannot be recovered.\n");
        return 0;
    }

    // Calculate inverse of plaintext matrix
    int PI[2][2];

    PI[0][0] = mod(inv * P[1][1]);
    PI[0][1] = mod(-inv * P[0][1]);
    PI[1][0] = mod(-inv * P[1][0]);
    PI[1][1] = mod(inv * P[0][0]);

    // Recover encryption key
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            K[i][j] = mod(C[i][0] * PI[0][j] +
                          C[i][1] * PI[1][j]);

    printf("Plaintext: %s\n", p);
    printf("Ciphertext: %s\n", c);

    printf("\nRecovered Key Matrix:\n");

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
            printf("%d ", K[i][j]);
        printf("\n");
    }

    return 0;
}

