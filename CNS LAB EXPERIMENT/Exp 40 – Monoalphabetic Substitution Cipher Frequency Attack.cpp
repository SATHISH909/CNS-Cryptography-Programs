
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char cipher[1000], decrypted[1000];
    int count[26] = {0};
    int cipherOrder[26], englishOrder[26];
    int i, j, temp, total = 0;
    char englishFreq[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    char mapping[26];

    printf("Enter encrypted text: ");
    fgets(cipher, sizeof(cipher), stdin);

    cipher[strcspn(cipher, "\n")] = '\0';

    /* Count encrypted letter frequencies */
    for (i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i])) {
            count[toupper((unsigned char)cipher[i]) - 'A']++;
            total++;
        }
    }

    /* Initialize alphabet indexes */
    for (i = 0; i < 26; i++) {
        cipherOrder[i] = i;
    }

    /* Sort cipher letters by frequency */
    for (i = 0; i < 26; i++) {
        for (j = i + 1; j < 26; j++) {
            if (count[cipherOrder[i]] < count[cipherOrder[j]]) {
                temp = cipherOrder[i];
                cipherOrder[i] = cipherOrder[j];
                cipherOrder[j] = temp;
            }
        }
    }

    /* Create frequency-based substitution mapping */
    for (i = 0; i < 26; i++) {
        mapping[cipherOrder[i]] = englishFreq[i];
    }

    /* Decrypt using the estimated mapping */
    for (i = 0; cipher[i] != '\0'; i++) {
        if (isupper((unsigned char)cipher[i])) {
            decrypted[i] = mapping[cipher[i] - 'A'];
        } else if (islower((unsigned char)cipher[i])) {
            decrypted[i] =
                tolower(mapping[toupper((unsigned char)cipher[i]) - 'A']);
        } else {
            decrypted[i] = cipher[i];
        }
    }

    decrypted[i] = '\0';

    printf("\nLetter Frequency Mapping:\n");
    for (i = 0; i < 26; i++) {
        printf("%c -> %c\n", 'A' + cipherOrder[i], englishFreq[i]);
    }

    printf("\nEstimated Decrypted Text:\n%s\n", decrypted);

    printf("\nTotal alphabetic characters: %d\n", total);

    return 0;
}

