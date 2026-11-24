
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Candidate {
    int shift;
    double score;
    char text[1000];
};

double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

int main() {
    char cipher[1000];
    int count[26], total, i, j, k;
    struct Candidate candidates[26], temp;

    printf("Enter encrypted text: ");
    fgets(cipher, sizeof(cipher), stdin);

    cipher[strcspn(cipher, "\n")] = '\0';

    for (k = 0; k < 26; k++) {
        for (i = 0; i < 26; i++)
            count[i] = 0;

        total = 0;

        strcpy(candidates[k].text, cipher);
        candidates[k].shift = k;

        for (i = 0; cipher[i] != '\0'; i++) {
            if (isalpha((unsigned char)cipher[i])) {
                int upper = isupper((unsigned char)cipher[i]);
                int value = toupper((unsigned char)cipher[i]) - 'A';

                int decrypted = (value - k + 26) % 26;

                candidates[k].text[i] =
                    upper ? decrypted + 'A' : decrypted + 'a';

                count[decrypted]++;
                total++;
            }
        }

        candidates[k].score = 0;

        if (total > 0) {
            for (j = 0; j < 26; j++) {
                double expected = total * englishFreq[j] / 100.0;
                double difference = count[j] - expected;

                candidates[k].score +=
                    (difference * difference) / expected;
            }
        }
    }

    /* Sort candidates by lowest chi-square score */
    for (i = 0; i < 26; i++) {
        for (j = i + 1; j < 26; j++) {
            if (candidates[i].score > candidates[j].score) {
                temp = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = temp;
            }
        }
    }

    printf("\nTop 10 possible decryptions:\n");

    for (i = 0; i < 10; i++) {
        printf("\nShift: %d", candidates[i].shift);
        printf("\nScore: %.2f", candidates[i].score);
        printf("\nPlaintext: %s\n", candidates[i].text);
    }

    return 0;
}

