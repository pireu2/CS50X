#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int only_digits(string text);
void rotate(string text, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (only_digits(argv[1]) == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string text = get_string("plaintext: ");
    rotate(text, key);
    printf("ciphertext: %s\n", text);

}

int only_digits(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isdigit(text[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void rotate(string text, int key)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                text[i] = text[i] - 'A';
                text[i] = ((int) text[i] + key) % 26;
                text[i] = text[i] + 'A';

            }
            if (islower(text[i]))
            {
                text[i] = text[i] - 'a';
                text[i] = ((int) text[i] + key) % 26;
                text[i] = text[i] + 'a';
            }
        }
    }
}