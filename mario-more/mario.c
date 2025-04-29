#include <cs50.h>
#include <stdio.h>

int answer;
int i;
int j;
int k;

int main(void)
{
    do
    {
        answer = get_int("Height?\n");
    }
    while (answer > 8 || answer < 1);

    for (i = 1; i <= answer; i++)
    {
        for (j = 0; j < answer - i; j++)
        {
            printf(" ");
        }
        for (k = 0; k < i; k++)
        {
            printf("#");
        }
        printf(" ");
        printf(" ");
        for (j = 0; j > answer + i; j++)
        {
            printf("1");
        }
        for (k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
