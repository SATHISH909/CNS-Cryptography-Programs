
#include <stdio.h>
#include <string.h>

#define BS 8
#define MAX 500

unsigned char key[BS] = "SECUREK";
unsigned char iv[BS] = "INITVEC";

void encryptBlock(unsigned char in[], unsigned char out[])
{
    int i;
    for(i = 0; i < BS; i++)
        out[i] = in[i] ^ key[i];
}

void decryptBlock(unsigned char in[], unsigned char out[])
{
    encryptBlock(in, out);
}

void printHex(unsigned char data[], int len)
{
    int i;
    for(i = 0; i < len; i++)
        printf("%02X ", data[i]);
    printf("\n");
}

int main()
{
    unsigned char text[MAX], padded[MAX];
    unsigned char ecb[MAX], cbc[MAX], cfb[MAX];
    unsigned char output[MAX], temp[BS], previous[BS];
    int len, pad, total, i, j;

    printf("Enter plaintext: ");
    fgets((char *)text, MAX, stdin);

    len = strlen((char *)text);

    if(len > 0 && text[len-1] == '\n')
        len--;

    // Padding: 0x80 followed by zero bytes
    pad = BS - (len % BS);

    if(pad == 0)
        pad = BS;

    memcpy(padded, text, len);
    padded[len] = 0x80;

    for(i = len + 1; i < len + pad; i++)
        padded[i] = 0;

    total = len + pad;

    printf("\nPadded Plaintext (Hex):\n");
    printHex(padded, total);

    // ECB Encryption
    for(i = 0; i < total; i += BS)
        encryptBlock(padded + i, ecb + i);

    printf("\nECB Ciphertext:\n");
    printHex(ecb, total);

    // CBC Encryption
    memcpy(previous, iv, BS);

    for(i = 0; i < total; i += BS)
    {
        for(j = 0; j < BS; j++)
            temp[j] = padded[i+j] ^ previous[j];

        encryptBlock(temp, cbc+i);

        memcpy(previous, cbc+i, BS);
    }

    printf("\nCBC Ciphertext:\n");
    printHex(cbc, total);

    // CFB Encryption
    memcpy(previous, iv, BS);

    for(i = 0; i < total; i += BS)
    {
        encryptBlock(previous, temp);

        for(j = 0; j < BS; j++)
            cfb[i+j] = padded[i+j] ^ temp[j];

        memcpy(previous, cfb+i, BS);
    }

    printf("\nCFB Ciphertext:\n");
    printHex(cfb, total);

    // CBC Decryption
    memcpy(previous, iv, BS);

    for(i = 0; i < total; i += BS)
    {
        decryptBlock(cbc+i, temp);

        for(j = 0; j < BS; j++)
            output[i+j] = temp[j] ^ previous[j];

        memcpy(previous, cbc+i, BS);
    }

    printf("\nDecrypted CBC Text:\n");
    for(i = 0; i < len; i++)
        printf("%c", output[i]);

    printf("\n");

    return 0;
}

