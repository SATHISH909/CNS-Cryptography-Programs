
#include <stdio.h>

int gcdExtended(int a, int b, int *x, int *y) {
    int x1, y1, gcd;

    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    gcd = gcdExtended(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd;
}

int main() {
    int n = 3599;
    int e = 31;
    int p, q, phi;
    int x, y, d;

    /* Find prime factors of n */
    for (p = 2; p <= n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    phi = (p - 1) * (q - 1);

    /* Find modular inverse of e */
    gcdExtended(e, phi, &x, &y);

    d = (x % phi + phi) % phi;

    printf("RSA Private Key Generation\n");
    printf("--------------------------\n");
    printf("Public Key e = %d\n", e);
    printf("Modulus n = %d\n", n);
    printf("Prime factor p = %d\n", p);
    printf("Prime factor q = %d\n", q);
    printf("Phi(n) = %d\n", phi);
    printf("Private Key d = %d\n", d);

    printf("\nPublic Key  = (%d, %d)\n", e, n);
    printf("Private Key = (%d, %d)\n", d, n);

    return 0;
}

