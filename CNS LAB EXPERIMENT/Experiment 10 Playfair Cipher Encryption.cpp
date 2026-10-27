
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char key[5][5] = {
    {'M','F','H','I','K'},
    {'U','N','O','P','Q'},
    {'Z','V','W','X','Y'},
    {'E','L','A','R','G'},
    {'D','S','T','B','C'}
};

void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            if (key[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
}

int main()
{
    char text[500], plain[500], a, b;
    int i, j = 0, r1, c1, r2, c2;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i] != '\0'; i++)
        if (isalpha((unsigned char)text[i]))
        {
            a = toupper((unsigned char)text[i]);
            if (a == 'J')
                a = 'I';
            plain[j++] = a;
        }

    plain[j] = '\0';

    printf("Encrypted text: ");

    for (i = 0; i < j; )
    {
        a = plain[i++];

        if (i < j && plain[i] == a)
            b = 'X';
        else if (i < j)
            b = plain[i++];
        else
            b = 'X';

        findPosition(a, &r1, &c1);
        findPosition(b, &r2, &c2);

        if (r1 == r2)
        {
            putchar(key[r1][(c1 + 1) % 5]);
            putchar(key[r2][(c2 + 1) % 5]);
        }
        else if (c1 == c2)
        {
            putchar(key[(r1 + 1) % 5][c1]);
            putchar(key[(r2 + 1) % 5][c2]);
        }
        else
        {
            putchar(key[r1][c2]);
            putchar(key[r2][c1]);
        }
    }

    printf("\n");
    return 0;
}
