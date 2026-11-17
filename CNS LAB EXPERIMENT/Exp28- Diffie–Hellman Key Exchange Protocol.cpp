
#include <stdio.h>

long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;

    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int main() {
    int q = 23, a = 5;
    int aliceSecret = 6;
    int bobSecret = 15;

    int alicePublic, bobPublic;
    int aliceKey, bobKey;
    int aliceWrong, bobWrong;
    int inverse = -1, i;

    printf("DIFFIE-HELLMAN KEY EXCHANGE\n");
    printf("--------------------------\n");

    printf("Public prime q = %d\n", q);
    printf("Public base a = %d\n", a);

    /* Standard Diffie-Hellman */
    alicePublic = powerMod(a, aliceSecret, q);
    bobPublic = powerMod(a, bobSecret, q);

    aliceKey = powerMod(bobPublic, aliceSecret, q);
    bobKey = powerMod(alicePublic, bobSecret, q);

    printf("\nStandard Diffie-Hellman:\n");
    printf("Alice secret = %d\n", aliceSecret);
    printf("Bob secret = %d\n", bobSecret);
    printf("Alice public value = %d\n", alicePublic);
    printf("Bob public value = %d\n", bobPublic);
    printf("Alice shared key = %d\n", aliceKey);
    printf("Bob shared key = %d\n", bobKey);

    if (aliceKey == bobKey)
        printf("Shared key established successfully.\n");

    /* Demonstrate the alternative x^a */
    aliceWrong = powerMod(aliceSecret, a, q);
    bobWrong = powerMod(bobSecret, a, q);

    printf("\nIf they send x^a instead:\n");
    printf("Alice sends = %d\n", aliceWrong);
    printf("Bob sends = %d\n", bobWrong);

    /* Find inverse of a modulo q-1 */
    for (i = 1; i < q - 1; i++) {
        if ((a * i) % (q - 1) == 1) {
            inverse = i;
            break;
        }
    }

    if (inverse != -1) {
        printf("\nAttacker can recover the secrets:\n");
        printf("Inverse of a modulo q-1 = %d\n", inverse);

        printf("Recovered Alice secret = %lld\n",
               powerMod(aliceWrong, inverse, q));

        printf("Recovered Bob secret = %lld\n",
               powerMod(bobWrong, inverse, q));
    }

    return 0;
}

