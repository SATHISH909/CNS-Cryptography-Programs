
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 2000

int main()
{
    char cipher[MAX];
    char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    char decrypted[MAX];
    int freq[26] = {0};
    int used[26] = {0};
    int order[26];
    int i, j, temp;

    printf("Enter ciphertext: ");
    fgets(cipher, MAX, stdin);

    // Count letter frequencies
    for (i = 0; cipher[i] != '\0'; i++)
        if (isalpha((unsigned char)cipher[i]))
            freq[toupper((unsigned char)cipher[i]) - 'A']++;

    // Sort letters by frequency
    for (i = 0; i < 26; i++)
        order[i] = i;

    for (i = 0; i < 25; i++)
        for (j = i + 1; j < 26; j++)
            if (freq[order[j]] > freq[order[i]])
            {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }

    // Generate substitution mapping
    char key[26];

    for (i = 0; i < 26; i++)
        key[order[i]] = english[i];

    // Decrypt ciphertext
    for (i = 0; cipher[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)cipher[i]))
        {
            int index = toupper((unsigned char)cipher[i]) - 'A';
            decrypted[i] = key[index];
        }
        else
            decrypted[i] = cipher[i];
    }

    decrypted[i] = '\0';

    printf("\nLetter Frequency Analysis:\n");

    for (i = 0; i < 26; i++)
        printf("%c : %d\n", 'A' + order[i],
               freq[order[i]]);

    printf("\nEstimated Decrypted Text:\n%s\n", decrypted);

    return 0;
}

