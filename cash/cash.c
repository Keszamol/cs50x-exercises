#include <cs50.h>
#include <stdio.h>

int quarter;
int quarter2;
int dime;
int dime2;
int nickel;
int nickel2;
int pennie;
int pennie2;
int sum;

int answer;
int rest;

int main(void)
{
    do
    {
        answer = get_int("Change owed:\n");
    }
    while (answer < 0);

    quarter = answer / 25;
    quarter2 = answer - (quarter * 25);

    dime = quarter2 / 10;
    dime2 = quarter2 - (dime * 10);

    nickel = dime2 / 5;
    nickel2 = dime2 - (nickel * 5);

    pennie = nickel2 / 1;

    sum = quarter + dime + nickel + pennie;
    printf("%i\n", sum);
}
