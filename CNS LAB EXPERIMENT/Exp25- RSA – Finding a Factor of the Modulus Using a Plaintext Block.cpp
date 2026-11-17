
#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n, m, g;

    printf("RSA Factor Detection\n");
    printf("--------------------\n");

    printf("Enter RSA modulus n: ");
    scanf("%d", &n);

    printf("Enter plaintext block m: ");
    scanf("%d", &m);

    g = gcd(m, n);

    printf("\nGCD(%d, %d) = %d\n", m, n, g);

    if (g == 1) {
        printf("No common factor found.\n");
        printf("The plaintext block does not reveal a factor.\n");
    }
    else if (g == n) {
        printf("The plaintext block is divisible by n.\n");
        printf("No non-trivial factor is revealed.\n");
    }
    else {
        printf("A non-trivial factor is discovered!\n");
        printf("One factor = %d\n", g);
        printf("Other factor = %d\n", n / g);
        printf("RSA modulus can be factored.\n");
    }

    return 0;
}

