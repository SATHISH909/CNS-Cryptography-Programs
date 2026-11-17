
#include <stdio.h>

int gcdExtended(int a, int b, int *x, int *y) {
    int x1, y1, g;

    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    g = gcdExtended(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return g;
}

int main() {
    int n = 3233;
    int oldE = 17, oldD = 2753;
    int p, q, phi;
    int newE = 7, x, y, newD;

    printf("RSA Key Replacement Demonstration\n");
    printf("---------------------------------\n");

    printf("Original modulus n = %d\n", n);
    printf("Leaked private exponent d = %d\n", oldD);

    /* Factor the reused modulus */
    for (p = 2; p <= n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    phi = (p - 1) * (q - 1);

    printf("\nFactors of reused modulus:\n");
    printf("p = %d, q = %d\n", p, q);
    printf("Phi(n) = %d\n", phi);

    /* Generate a new private exponent */
    if (gcdExtended(newE, phi, &x, &y) != 1) {
        printf("Invalid new public exponent.\n");
        return 0;
    }

    newD = (x % phi + phi) % phi;

    printf("\nNew public exponent e = %d\n", newE);
    printf("New private exponent d = %d\n", newD);

    printf("\nNew public key  = (%d, %d)\n", newE, n);
    printf("New private key = (%d, %d)\n", newD, n);

    printf("\nConclusion: Reusing the same modulus is NOT safe.\n");

    return 0;
}

