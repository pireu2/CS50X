#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        printf("Start size: ");
        scanf("%i", &start);
    }
    while (start < 9);
    // TODO: Prompt for end size
    int end;
    do
    {
        printf("End size: ");
        scanf("%i", &end);
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int i = 0;
    while (start < end)
    {
        start = start + (start / 3) - (start / 4);
        i++;
    }


    // TODO: Print number of years
    printf("Years: %i\n", i);
}
