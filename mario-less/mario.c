#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int j;
    int number;
    do
    {
        number = get_int("Height?\n");
    }
    while (number < 1 || number > 8);

    for (int i = 1; i <= number; i++)
    {
        for (int k = 0; k < number - i; k++)
        {
            printf(" ");
        }
        for (j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
