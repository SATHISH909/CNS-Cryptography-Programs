
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "");

    wchar_t cipher[] =
        L"53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83\n"
        L"(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*\n"
        L";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81\n"
        L"(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";

    wchar_t key[65536];
    wchar_t c, p;
    int i;

    for (i = 0; i < 65536; i++)
        key[i] = (wchar_t)i;

    wprintf(L"SIMPLE SUBSTITUTION CIPHER\n");
    wprintf(L"Enter mapping: cipher_symbol plaintext_letter\n");
    wprintf(L"Example: ‡ e\n");
    wprintf(L"Enter ! ! to finish mapping.\n\n");

    while (wscanf(L" %lc %lc", &c, &p) == 2)
    {
        if (c == L'!' && p == L'!')
            break;

        if ((unsigned int)c < 65536)
            key[c] = p;
    }

    wprintf(L"\nDecrypted message:\n");

    for (i = 0; cipher[i] != L'\0'; i++)
    {
        c = cipher[i];

        if (iswspace(c))
            putwchar(c);
        else if ((unsigned int)c < 65536 && key[c] != c)
            putwchar(key[c]);
        else
            putwchar(L'_');
    }

    wprintf(L"\n");
    return 0;
}
