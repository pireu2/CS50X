#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void encrypt(string text, string key);
int is_valid(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (is_valid(argv[1]) == 0)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    encrypt(text, argv[1]);
    printf("ciphertext: %s\n", text);
}

int is_valid(string key)
{
    if (strlen(key) != 26)
    {
        return 0;
    }

    int arr[26] = {0};

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return 0;
        }
        if (isupper(key[i]))
        {
            arr[(int) key[i] - 'A']++;
        }
        if (islower(key[i]))
        {
            arr[(int) key[i] - 'a']++;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (arr[i] != 1)
        {
            return 0;
        }
    }
    return 1;
}

void encrypt(string text, string key)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]))
        {
            int c = (int) text[i] - 'A';
            text[i] = toupper(key[c]);
        }
        else if (islower(text[i]))
        {
            int c = (int) text[i] - 'a';
            text[i] = tolower(key[c]);
        }
    }
}