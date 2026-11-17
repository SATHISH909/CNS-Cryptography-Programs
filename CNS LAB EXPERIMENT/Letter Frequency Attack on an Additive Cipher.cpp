
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

float english[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

int main()
{
    char cipher[MAX], result[26][MAX];
    float score[26], temp;
    int i, j, k, count, total = 0;

    printf("Enter ciphertext: ");
    fgets(cipher, MAX, stdin);

    for (k = 0; k < 26; k++)
    {
        int freq[26] = {0};
        count = 0;

        for (i = 0; cipher[i] != '\0'; i++)
        {
            if (isalpha((unsigned char)cipher[i]))
            {
                char ch = toupper((unsigned char)cipher[i]);
                int p = (ch - 'A' - k + 26) % 26;

                result[k][i] = p + 'A';
                freq[p]++;
                count++;
            }
            else
                result[k][i] = cipher[i];
        }

        result[k][i] = '\0';

        score[k] = 0;

        if (count > 0)
        {
            for (j = 0; j < 26; j++)
            {
                float expected = count * english[j] / 100.0;
                float difference = freq[j] - expected;

                score[k] += difference * difference / expected;
            }
        }
    }

    printf("\nTop 10 Possible Plaintexts:\n");

    for (i = 0; i < 10; i++)
    {
        int best = -1;

        for (j = 0; j < 26; j++)
        {
            if (score[j] >= 0 &&
                (best == -1 || score[j] < score[best]))
                best = j;
        }

        if (best == -1)
            break;

        printf("\nShift %d: %s", best, result[best]);
        score[best] = -1;
    }

    return 0;
}

