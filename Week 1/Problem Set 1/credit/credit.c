#include <cs50.h>
#include <stdio.h>

int checksum(long n);
int nodigits(long n);
void identify(long n);

int main(void)
{
    long n;
    n = get_long("Number: ");
    if (checksum(n) == 0)
    {
        printf("INVALID\n");
    }
    else
    {
        identify(n);
    }
}

int nodigits(long n)
{
    long temp = n;
    int i = 0;
    while (temp)
    {
        temp /= 10;
        i++;
    }

    return i;
}

void identify(long n)
{
    if (nodigits(n) == 15)
    {
        if (n / 10000000000000 == 34 || n / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (nodigits(n) == 16)
    {
        long tmp = n / 100000000000000;
        if (n / 1000000000000000 == 4)
        {
            printf("VISA\n");
        }
        else if (tmp == 51 || tmp == 52 || tmp == 53 || tmp == 54 || tmp == 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (nodigits(n) == 13)
    {
        if (n / 1000000000000 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int checksum(long n)
{
    long temp = n;
    int sum = 0;
    int i = 0;
    while (temp)
    {
        if (i == 0)
        {
            sum += temp % 10;
            i = 1;
        }
        else if (i == 1)
        {
            if ((temp % 10) * 2 > 9)
            {
                sum = sum + ((temp % 10) * 2) / 10 + ((temp % 10) * 2) % 10;
            }
            else
            {
                sum = sum + (temp % 10) * 2;
            }
            i = 0;
        }
        temp /= 10;
    }
    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}