#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //input for the height
    int n;
    do
    {
        printf("Height: ");
        scanf("%i", &n);
    }
    while (n < 1 || n > 8);

    //print pyramids
    for (int i = 1; i <= n; i++)
    {
        //print first whitespaces
        for (int j = 0; j < n - i; j++)
        {
            printf(" ");
        }
        //prints first pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        //print separator
        printf("  ");
        //print secod pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        //print new line for the next row of the pyramids
        printf("\n");
    }
}