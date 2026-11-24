
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

/* English letters arranged by frequency */
const char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

int main()
{
    char cipher[MAX];
    int freq[26] = {0};
    int order[26];
    int i, j, temp;

    printf("MONOALPHABETIC SUBSTITUTION - FREQUENCY ATTACK\n");
    printf("Enter the ciphertext:\n");
    fgets(cipher, MAX, stdin);

    /* Count the frequency of each ciphertext letter */
    for (i = 0; cipher[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)cipher[i]))
        {
            freq[toupper((unsigned char)cipher[i]) - 'A']++;
        }
    }

    /* Store alphabet indexes */
    for (i = 0; i < 26; i++)
        order[i] = i;

    /* Sort letters by descending frequency */
    for (i = 0; i < 25; i++)
    {
        for (j = i + 1; j < 26; j++)
        {
            if (freq[order[j]] > freq[order[i]])
            {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    printf("\nCiphertext letter frequencies:\n");
    for (i = 0; i < 26; i++)
    {
        if (freq[order[i]] > 0)
            printf("%c : %d\n", 'A' + order[i], freq[order[i]]);
    }

    printf("\nTOP 10 POSSIBLE PLAINTEXTS:\n");

    /* Generate frequency-based candidate substitutions */
    for (int shift = 0; shift < 10; shift++)
    {
        char plain[MAX];

        for (i = 0; cipher[i] != '\0'; i++)
        {
            if (isalpha((unsigned char)cipher[i]))
            {
                int index = toupper((unsigned char)cipher[i]) - 'A';
                int rank = 0;

                while (rank < 26 && order[rank] != index)
                    rank++;

                char decoded = english[(rank + shift) % 26];

                if (islower((unsigned char)cipher[i]))
                    plain[i] = tolower(decoded);
                else
                    plain[i] = decoded;
            }
            else
            {
                plain[i] = cipher[i];
            }
        }

        plain[i] = '\0';

        printf("\nCandidate %d: %s\n", shift + 1, plain);
    }

    return 0;
}

