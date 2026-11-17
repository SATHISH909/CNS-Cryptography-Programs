
#include <stdio.h>
#include <string.h>

int PC1[56] = {
57,49,41,33,25,17,9,1,58,50,42,34,26,18,
10,2,59,51,43,35,27,19,11,3,60,52,44,36,
63,55,47,39,31,23,15,7,62,54,46,38,30,22,
14,6,61,53,45,37,29,21,13,5,28,20,12,4
};

int PC2[48] = {
14,17,11,24,1,5,3,28,15,6,21,10,
23,19,12,4,26,8,16,7,27,20,13,2,
41,52,31,37,47,55,30,40,51,45,33,48,
44,49,39,56,34,53,46,42,50,36,29,32
};

int shifts[16] = {
1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

unsigned long long permute(
    unsigned long long input,
    int table[], int n, int bits)
{
    unsigned long long output = 0;
    int i;

    for(i = 0; i < n; i++)
    {
        output <<= 1;
        output |= (input >> (bits - table[i])) & 1ULL;
    }

    return output;
}

unsigned long long hexToLong(char str[])
{
    unsigned long long value = 0;
    int i, digit;

    for(i = 0; i < 16; i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
            digit = str[i] - '0';
        else if(str[i] >= 'A' && str[i] <= 'F')
            digit = str[i] - 'A' + 10;
        else if(str[i] >= 'a' && str[i] <= 'f')
            digit = str[i] - 'a' + 10;
        else
            return 0;

        value = (value << 4) | digit;
    }

    return value;
}

int main()
{
    char keyInput[20];
    unsigned long long key, pc1, combined;
    unsigned long long subkey;
    unsigned int C, D;
    int i;

    printf("Enter 16-digit hexadecimal key: ");
    scanf("%19s", keyInput);

    if(strlen(keyInput) != 16)
    {
        printf("Invalid key! Enter 16 hexadecimal digits.\n");
        return 1;
    }

    key = hexToLong(keyInput);

    if(key == 0)
    {
        printf("Invalid hexadecimal key.\n");
        return 1;
    }

    // Apply PC-1 permutation
    pc1 = permute(key, PC1, 56, 64);

    // Divide into two 28-bit halves
    C = (unsigned int)(pc1 >> 28);
    D = (unsigned int)(pc1 & 0x0FFFFFFF);

    printf("\nDES SUBKEY GENERATION\n");
    printf("-----------------------------\n");

    for(i = 0; i < 16; i++)
    {
        // Circular left shift
        C = ((C << shifts[i]) |
             (C >> (28 - shifts[i]))) & 0x0FFFFFFF;

        D = ((D << shifts[i]) |
             (D >> (28 - shifts[i]))) & 0x0FFFFFFF;

        // Combine both halves
        combined = ((unsigned long long)C << 28) | D;

        // Apply PC-2 permutation
        subkey = permute(combined, PC2, 48, 56);

        printf("K%-2d = %012llX\n", i + 1, subkey);
    }

    return 0;
}

