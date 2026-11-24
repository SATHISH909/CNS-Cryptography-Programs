
#include <stdio.h>
#include <string.h>

int mod26(int n)
{
    return (n % 26 + 26) % 26;
}

int inverse(int n)
{
    int i;
    for (i = 1; i < 26; i++)
    {
        if ((n * i) % 26 == 1)
            return i;
    }
    return -1;
}

int main()
{
    char plain[5], cipher[5];
    int P[2][2], C[2][2], K[2][2];
    int det, detInv;
    int i, j;

    printf("HILL CIPHER - KNOWN PLAINTEXT ATTACK\n");
    printf("------------------------------------\n");

    printf("Enter 4 plaintext letters: ");
    scanf("%4s", plain);

    printf("Enter corresponding 4 ciphertext letters: ");
    scanf("%4s", cipher);

    /* Convert letters into matrix columns */
    for (i = 0; i < 2; i++)
    {
        P[0][i] = plain[2 * i] - 'A';
        P[1][i] = plain[2 * i + 1] - 'A';

        C[0][i] = cipher[2 * i] - 'A';
        C[1][i] = cipher[2 * i + 1] - 'A';
    }

    /* Calculate determinant of plaintext matrix */
    det = mod26(P[0][0] * P[1][1] -
                P[0][1] * P[1][0]);

    detInv = inverse(det);

    if (detInv == -1)
    {
        printf("\nAttack failed: Plaintext matrix is not invertible modulo 26.\n");
        return 0;
    }

    /* Calculate inverse of plaintext matrix */
    int Pinv[2][2];

    Pinv[0][0] = mod26(detInv * P[1][1]);
    Pinv[0][1] = mod26(-detInv * P[0][1]);
    Pinv[1][0] = mod26(-detInv * P[1][0]);
    Pinv[1][1] = mod26(detInv * P[0][0]);

    /* Recover key: K = C * inverse(P) mod 26 */
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            K[i][j] = mod26(
                C[i][0] * Pinv[0][j] +
                C[i][1] * Pinv[1][j]
            );
        }
    }

    printf("\nRecovered Hill Cipher Key:\n");

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
            printf("%d ", K[i][j]);

        printf("\n");
    }

    printf("\nKey recovery successful!\n");

    return 0;
}

