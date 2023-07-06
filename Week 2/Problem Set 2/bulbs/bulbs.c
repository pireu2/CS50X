#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void convert_string(string text);

int main(void)
{
    string text = get_string("Message: ");
    convert_string(text);
}

void convert_string(string text)
{
    int n = strlen(text);
    int a[n][8];
    for (int i = 0; i < n; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            int k = (int) text[i] >> j;
            if (k & 1)
            {
                a[i][j] = 1;
            }
            else
            {
                a[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            print_bulb(a[i][j]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
