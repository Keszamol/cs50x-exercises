#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char letters_upper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char new_letters[] = {};

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2) // Prüft ob argc 1 oder mehr als 2 eingaben hat
    {
        printf("Error: no or to much input\n"); // Falls ja erscheint die Errormessage
        return 1;
    }

    string input = argv[1];
    int key =
        atoi(argv[1]); // Abfrage der zweiten Eingabe in der command line und Umwandlung in INT
    int key_length = strlen(argv[1]); // Berechnung der Stellen von key

    for (int i = 0; i < key_length; i++) // Geht die Stellen von input durch
    {
        if (isdigit(input[i])) // Prüft jede Stelle ob es eine Zahl ist
        {
            continue; // Wenn es durchläuft und alles eine Zahl ist endet die for Schleife
        }
        else
        {
            printf("Usage: ./caesar key\n"); // Ist es keine Zahl kommt die Anwendungserklärung
            return 1;                        // Die Schleife wird abgebrochen
        }
    }
    string text = get_string("plaintext:  "); // Abfrage des plaintext
    int text_length = strlen(text);           // Berechnung der Stellen von plaintext

    for (int i = 0; i < text_length; i++) // Geht jeden char des plaintext durch
    {
        for (int j = 0; j < 26; j++) // Geht den aktuellen index 26 mal in letters durch
        {
            if (text[i] == letters[j]) // Wenn die Buchstaben übereinstimmen
            {
                int letter_number = j; // Dann wird die Zahl des Buchstaben ausgegeben als int
                                       // variable letter_number
                int codiert =
                    (letter_number + key) %
                    26; // Rechnet den key auf die Nummer und zwischenspeichert als codiert
                new_letters[i] = letters[codiert]; // Definiert new_letter als codierte variante und
                                                   // speichert alle Kleinbuchstaben im array
            }
            else if (text[i] == letters_upper[j]) // Prüft die Groß- und Kleinschreibung
            {
                int letter_number = j;
                int codiert = letter_number + key;
                new_letters[i] =
                    letters_upper[codiert]; // Definiert new_letter als codierte variante und
                                            // speichert alle Großbuchstaben im array
            }
            else if (isdigit(text[i])) // Prüft ob es eine Zahl ist
            {
                new_letters[i] = text[i]; // Falls ja wird die Zahl einfach durchgegeben
            }
            else if (ispunct(text[i])) // Prüft ob es ein Satzzeichen ist
            {
                new_letters[i] = text[i]; // Falls ja wird die Zahl einfach durchgegeben
            }
            else if (isspace(text[i])) // Prüft ob es ein Leerzeichen ist
            {
                new_letters[i] = text[i]; // Falls ja wird die Zahl einfach durchgegeben
            }
        }
    }
    printf("ciphertext: %s\n", new_letters); // Printet den Ciphercode
    return 0;
}
