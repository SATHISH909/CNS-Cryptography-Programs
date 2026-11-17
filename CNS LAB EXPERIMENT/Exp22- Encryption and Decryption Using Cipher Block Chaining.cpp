
#include <stdio.h>

int P10[10] = {3,5,2,7,4,10,1,9,8,6};
int P8[8] = {6,3,7,4,8,5,10,9};
int IP[8] = {2,6,3,1,4,8,5,7};
int IP1[8] = {4,1,3,5,7,2,8,6};
int EP[8] = {4,1,2,3,2,3,4,1};
int P4[4] = {2,4,3,1};

int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

int permute(int n, int table[], int size, int bits)
{
    int result = 0, i;

    for(i = 0; i < size; i++)
    {
        result = (result << 1) |
                 ((n >> (bits - table[i])) & 1);
    }

    return result;
}

int leftShift(int n, int shift)
{
    return ((n << shift) | (n >> (5-shift))) & 31;
}

void generateKeys(int key, int *k1, int *k2)
{
    int p, l, r;

    p = permute(key, P10, 10, 10);

    l = (p >> 5) & 31;
    r = p & 31;

    l = leftShift(l, 1);
    r = leftShift(r, 1);

    *k1 = permute((l << 5) | r, P8, 8, 10);

    l = leftShift(l, 2);
    r = leftShift(r, 2);

    *k2 = permute((l << 5) | r, P8, 8, 10);
}

int substitute(int value, int box[4][4])
{
    int row, col;

    row = ((value & 8) >> 2) | (value & 1);
    col = (value >> 1) & 3;

    return box[row][col];
}

int functionF(int value, int key)
{
    int l, r, ep, s, a, b;

    l = (value >> 4) & 15;
    r = value & 15;

    ep = permute(r, EP, 8, 4);
    ep = ep ^ key;

    a = (ep >> 4) & 15;
    b = ep & 15;

    s = (substitute(a, S0) << 2) |
         substitute(b, S1);

    s = permute(s, P4, 4, 4);

    return ((l ^ s) << 4) | r;
}

int swap(int n)
{
    return ((n & 15) << 4) | ((n >> 4) & 15);
}

int encrypt(int plain, int k1, int k2)
{
    int x;

    x = permute(plain, IP, 8, 8);
    x = functionF(x, k1);
    x = swap(x);
    x = functionF(x, k2);

    return permute(x, IP1, 8, 8);
}

int decrypt(int cipher, int k1, int k2)
{
    int x;

    x = permute(cipher, IP, 8, 8);
    x = functionF(x, k2);
    x = swap(x);
    x = functionF(x, k1);

    return permute(x, IP1, 8, 8);
}

int main()
{
    int key = 0x1FD;
    int iv = 0xAA;

    int plain[2] = {0x01, 0x23};
    int cipher[2], recovered[2];

    int k1, k2, previous;
    int i;

    generateKeys(key, &k1, &k2);

    printf("S-DES CBC ENCRYPTION AND DECRYPTION\n");
    printf("-----------------------------------\n");

    printf("Key: 0111111101\n");
    printf("IV : 10101010\n");

    // Encryption
    previous = iv;

    printf("\nEncrypted Ciphertext:\n");

    for(i = 0; i < 2; i++)
    {
        cipher[i] = encrypt(plain[i] ^ previous, k1, k2);

        printf("%02X : ", cipher[i]);

        {
            int j;
            for(j = 7; j >= 0; j--)
                printf("%d", (cipher[i] >> j) & 1);
        }

        printf("\n");
        previous = cipher[i];
    }

    // Decryption
    previous = iv;

    printf("\nDecrypted Plaintext:\n");

    for(i = 0; i < 2; i++)
    {
        recovered[i] = decrypt(cipher[i], k1, k2) ^ previous;

        printf("%02X : ", recovered[i]);

        {
            int j;
            for(j = 7; j >= 0; j--)
                printf("%d", (recovered[i] >> j) & 1);
        }

        printf("\n");
        previous = cipher[i];
    }

    printf("\nOriginal Plaintext: 00000001 00100011\n");
    printf("Recovered Plaintext: ");

    for(i = 0; i < 2; i++)
        printf("%08d ", 0);

    printf("\n");

    return 0;
}

