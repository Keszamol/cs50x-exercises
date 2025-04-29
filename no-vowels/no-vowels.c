// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

char new_string[] = {};

string replace(string user_string, int user_count);

int main(int argc, string argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    string user_string = argv[1];
    int user_count = strlen(user_string);

    replace(user_string, user_count);

    printf("%s\n", new_string);
}

string replace(string user_string, int user_count)
{
    for (int i = 0; i < user_count; i++)
    {
        if (user_string[i] == 'a')
        {
            new_string[i] = '6';
        }

        else if (user_string[i] == 'e')
        {
            new_string[i] = '3';
        }

        else if (user_string[i] == 'i')
        {
            new_string[i] = '1';
        }

        else if (user_string[i] == 'o')
        {
            new_string[i] = '0';
        }

        else
        {
            new_string[i] = user_string[i];
        }
    }

    return new_string;
}
