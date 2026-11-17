
#include <stdio.h>

int perm(int x, int t[], int n, int len) {
    int i, y = 0;
    for (i = 0; i < len; i++)
        y = (y << 1) | ((x >> (n - t[i])) & 1);
    return y;
}

int P10[] = {3,5,2,7,4,10,1,9,8,6};
int P8[]  = {6,3,7,4,8,5,10,9};
int IP[]  = {2,6,3,1,4,8,5,7};
int IPI[] = {4,1,3,5,7,2,8,6};
int EP[]  = {4,1,2,3,2,3,4,1};
int P4[]  = {2,4,3,1};

int S0[4][4] = {
    {1,0,3,2}, {3,2,1,0},
    {0,2,1,3}, {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3}, {2,0,1,3},
    {3,0,1,0}, {2,1,0,3}
};

int K1, K2;

int sbox(int x, int S[4][4]) {
    int row = ((x & 8) >> 2) | (x & 1);
    int col = (x >> 1) & 3;
    return S[row][col];
}

void generateKeys(int key) {
    int p, l, r;

    p = perm(key, P10, 10, 10);
    l = (p >> 5) & 31;
    r = p & 31;

    l = ((l << 1) | (l >> 4)) & 31;
    r = ((r << 1) | (r >> 4)) & 31;
    K1 = perm((l << 5) | r, P8, 10, 8);

    l = ((l << 2) | (l >> 3)) & 31;
    r = ((r << 2) | (r >> 3)) & 31;
    K2 = perm((l << 5) | r, P8, 10, 8);
}

int fk(int x, int key) {
    int l = (x >> 4) & 15;
    int r = x & 15;
    int v = perm(r, EP, 4, 8) ^ key;

    int s = (sbox((v >> 4) & 15, S0) << 2)
            | sbox(v & 15, S1);

    return ((l ^ perm(s, P4, 4, 4)) << 4) | r;
}

int sdes(int x) {
    x = perm(x, IP, 8, 8);
    x = fk(x, K1);
    x = ((x & 15) << 4) | (x >> 4);
    x = fk(x, K2);
    return perm(x, IPI, 8, 8);
}

void printBinary(int x) {
    int i;
    for (i = 7; i >= 0; i--)
        printf("%d", (x >> i) & 1);
}

int main() {
    int key = 509;  /* 0111111101 */
    int plain[3] = {1, 2, 4};
    int cipher[3], recovered[3];
    int i, counter, keystream;

    generateKeys(key);

    printf("CTR Mode - S-DES\n");
    printf("Plaintext : ");

    for (i = 0; i < 3; i++) {
        printBinary(plain[i]);
        printf(" ");
    }

    printf("\n\nEncryption:\n");

    for (i = 0; i < 3; i++) {
        counter = i;
        keystream = sdes(counter);
        cipher[i] = plain[i] ^ keystream;

        printf("Counter %d: ", counter);
        printBinary(counter);
        printf("  Keystream: ");
        printBinary(keystream);
        printf("  Ciphertext: ");
        printBinary(cipher[i]);
        printf("\n");
    }

    printf("\nFinal Ciphertext: ");
    for (i = 0; i < 3; i++) {
        printBinary(cipher[i]);
        printf(" ");
    }

    printf("\n\nDecryption:\n");

    for (i = 0; i < 3; i++) {
        counter = i;
        keystream = sdes(counter);
        recovered[i] = cipher[i] ^ keystream;

        printf("Recovered byte %d: ", i + 1);
        printBinary(recovered[i]);
        printf("\n");
    }

    printf("\nRecovered Plaintext: ");
    for (i = 0; i < 3; i++) {
        printBinary(recovered[i]);
        printf(" ");
    }

    printf("\n");
    return 0;
}

