#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string str = get_string("What is your name?\n");

    printf("hello, %s\n", str);
}