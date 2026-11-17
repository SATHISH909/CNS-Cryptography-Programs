
#include <stdio.h>

long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int inverse(int a, int mod) {
    int i;

    for (i = 1; i < mod; i++) {
        if ((a * i) % mod == 1)
            return i;
    }

    return -1;
}

void dsaSign(int hash, int x, int k, int p, int q,
             int g, int *r, int *s) {
    int kinv;

    *r = powerMod(g, k, p) % q;
    kinv = inverse(k, q);
    *s = (kinv * (hash + x * (*r))) % q;
}

int main() {
    int p = 23, q = 11, g = 2;
    int x = 3, y;
    int hash = 9;
    int r1, s1, r2, s2;

    int rsaN = 143;
    int rsaD = 103;
    int rsaSignature1, rsaSignature2;

    printf("DSA AND RSA SIGNATURE COMPARISON\n");
    printf("--------------------------------\n");

    /* DSA public key */
    y = powerMod(g, x, p);

    printf("DSA Public Key y = %d\n", y);
    printf("Message hash = %d\n", hash);

    /* Sign the same message using different k values */
    dsaSign(hash, x, 2, p, q, g, &r1, &s1);
    dsaSign(hash, x, 4, p, q, g, &r2, &s2);

    printf("\nDSA Signatures:\n");
    printf("First signature  = (%d, %d)\n", r1, s1);
    printf("Second signature = (%d, %d)\n", r2, s2);

    if (r1 != r2 || s1 != s2)
        printf("DSA signatures are different.\n");

    /* Basic deterministic RSA signature demonstration */
    rsaSignature1 = powerMod(hash, rsaD, rsaN);
    rsaSignature2 = powerMod(hash, rsaD, rsaN);

    printf("\nRSA Signatures:\n");
    printf("First signature  = %d\n", rsaSignature1);
    printf("Second signature = %d\n", rsaSignature2);

    if (rsaSignature1 == rsaSignature2)
        printf("RSA signatures are identical.\n");

    return 0;
}

