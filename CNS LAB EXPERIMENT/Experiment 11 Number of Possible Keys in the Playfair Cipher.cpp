
#include <stdio.h>
#include <math.h>

int main()
{
    long double total = 1, unique = 1;
    int i;

    for (i = 1; i <= 25; i++)
        total *= i;

    for (i = 1; i <= 24; i++)
        unique *= i;

    printf("Playfair Cipher Key Analysis\n");
    printf("----------------------------\n");

    printf("Total possible keys (25!): %.6Le\n", total);
    printf("Approximate key size: 2^%.2Lf\n", log2l(total));

    printf("\nEffectively unique keys (24!): %.6Le\n", unique);
    printf("Approximate unique key size: 2^%.2Lf\n",
           log2l(unique));

    return 0;
}
