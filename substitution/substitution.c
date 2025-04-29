#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char key_char[26] = {};
char letters_lower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char letters_upper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int command_line_conditions(string key, int key_length, int arguments);
string ciphertext(string plaintext, int plaintext_length);
bool conditions_not_ok = false;

int main(int argc, string argv[])
{
    int arguments = argc;

    if (arguments > 2 ||
        arguments < 2) // If more or less then two arguments in command line, error.
    {
        printf("To few, or many arguments.\nUsage: ./substitution key\n");
        conditions_not_ok = true;
        return 1;
    }

    int key_length = strlen(argv[1]);
    string key = argv[1];

    command_line_conditions(key, key_length, arguments);

    if (conditions_not_ok == true)
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    int plaintext_length = strlen(plaintext);

    ciphertext(plaintext, plaintext_length);
}

int command_line_conditions(string key, int key_length, int arguments)
{
    if (key_length < 26 || key_length > 26) // If key is less or more then 26 integers
    {
        printf("Wrong arguments!\nUsage: ./substitution key\n");
        conditions_not_ok = true;
        return 1;
    }

    for (int i = 0; i < key_length; i++)
    {
        if (isalpha(key[i])) // If key is alphabetical
        {
            continue;
        }
        else
        {
            printf("Not alphabetical!\nUsage: ./substitution key\n"); // If key is not alphabetical
            conditions_not_ok = true;
            return 1;
        }
    }

    for (int i = 0; i < key_length; i++)
    {
        if (conditions_not_ok == false)
        {
            key_char[i] = key[i];
            char key_letter = key[i];

            for (int j = 0; j < i; j++)
            {
                if (toupper(key_letter) == toupper(key_char[j])) // If key has duplicated letters
                {
                    printf("Duplicated letters\nUsage: ./substitution key\n");
                    conditions_not_ok = true;
                    return 1;
                }
            }
        }
    }
    return 0;
}

string ciphertext(string plaintext, int plaintext_length)
{
    char cipher[plaintext_length + 1] = {};

    for (int i = 0; i < plaintext_length; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (plaintext[i] == letters_upper[j])
            {
                cipher[i] = toupper(key_char[j]);
                break;
            }
            else if (plaintext[i] == letters_lower[j])
            {
                cipher[i] = tolower(key_char[j]);
                break;
            }
            else if (isdigit(plaintext[i]) || isspace(plaintext[i]) || ispunct(plaintext[i]))
            {
                cipher[i] = plaintext[i];
                break;
            }
        }
    }
    printf("ciphertext: %s\n", cipher);
    return 0;
}
