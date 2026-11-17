
#include <stdio.h>

int main()
{
    int n, errorBlock, i;

    printf("Enter number of blocks: ");
    scanf("%d", &n);

    printf("\nEnter corrupted ciphertext block number: ");
    scanf("%d", &errorBlock);

    if(n < 2 || errorBlock < 1 || errorBlock > n)
    {
        printf("Invalid input!\n");
        return 0;
    }

    // ECB Mode
    printf("\n--- ECB MODE ---\n");
    for(i = 1; i <= n; i++)
    {
        if(i == errorBlock)
            printf("P%d : CORRUPTED\n", i);
        else
            printf("P%d : CORRECT\n", i);
    }

    // CBC Mode
    printf("\n--- CBC MODE ---\n");
    for(i = 1; i <= n; i++)
    {
        if(i == errorBlock)
            printf("P%d : CORRUPTED (Cipher block error)\n", i);
        else if(i == errorBlock + 1)
            printf("P%d : ONE BIT FLIPPED\n", i);
        else
            printf("P%d : CORRECT\n", i);
    }

    // Plaintext error in first block
    printf("\n--- CBC PLAINTEXT ERROR ---\n");
    printf("If P1 contains an error:\n");

    for(i = 1; i <= n; i++)
        printf("C%d : AFFECTED\n", i);

    printf("\nAll subsequent ciphertext blocks are affected.\n");

    return 0;
}

