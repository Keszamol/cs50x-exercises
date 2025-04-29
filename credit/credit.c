#include <cs50.h>
#include <stdio.h>
#include <string.h>

string number;
int first_two_digits;
int first_digit;
int all_digits;
int digit;
int multiply;
int sum_second = 0;
int sum_first = 0;
int total;
int checksum;

int main(void)
{
    number = get_string("Number?:\n");

    first_two_digits = (number[0] - '0') * 10 + (number[1] - '0');
    first_digit = (number[0] - '0');
    all_digits = strlen(number);

    for (int i = all_digits - 2; i >= 0; i -= 2)
    {
        digit = number[i] - '0';
        multiply = digit * 2;

        if (multiply >= 10)
        {
            sum_second += (multiply % 10) + (multiply / 10);
        }
        else
        {
            sum_second += multiply;
        }
    }

    for (int i = all_digits - 1; i >= 0; i -= 2)
    {
        digit = number[i] - '0';
        sum_first += digit;
    }

    total = sum_second + sum_first;
    checksum = total % 10;

    if (checksum != 0)
    {
        printf("INVALID\n");
    }
    else if ((first_two_digits == 34 || first_two_digits == 37) && all_digits == 15)
    {
        printf("AMEX\n");
    }
    else if ((first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53 ||
              first_two_digits == 54 || first_two_digits == 55) &&
             all_digits == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((first_digit == 4) && (all_digits == 13 || all_digits == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
