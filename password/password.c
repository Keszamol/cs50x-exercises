// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int password_count;

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    password_count = strlen(password);

    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and "
               "symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_punct = false;

    for (int i = 0; i < password_count; i++)
    {
        if (isupper(password[i]))
        {
            has_upper = true;
        }

        if (islower(password[i]))
        {
            has_lower = true;
        }

        if (isdigit(password[i]))
        {
            has_digit = true;
        }

        if (ispunct(password[i]))
        {
            has_punct = true;
        }
    }

    if (has_upper == true && has_lower == true && has_digit == true && has_punct == true)
    {
        return true;
    }
    else
    {
        return false;
    }

    return false;
}
