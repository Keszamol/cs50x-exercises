#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int words_sum(void);
int average_letters(void);
int average_sentences(void);
int index(void);

string text;
int punctuation;
float L;
int sentence;
float S;
int formula;
int words;
int words_without_beginning;
int letters;
int count_letters;

int main(void)
{
    text = get_string("Text: "); // Erstelle eine String Abfrage für den Text

    count_letters = strlen(text);

    words_sum();
    average_letters();
    average_sentences();
    index();

    if (formula < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (formula > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", formula);
    }
}

int average_letters(void) // Berechnung von L
{

    for (int i = 0; i < count_letters; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
    }

    L = ((float) letters / words) *
        100; // count_letters_only / 100; Vermutlich fehlt noch die Anzahl der Wörter, ich hab
             // einfach 100 genommen. Bzw habe ich hier nicht wirklich den Durchschnitt je 100
             // Wörter.
    return letters;
}

int average_sentences(void) // Berechnung von S
{
    for (int i = 0; i < count_letters; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence += 1;
        }
    }

    S = ((float) sentence / words) *
        100; // Vermutlich fehlt noch die Anzahl der Wörter, ich hab einfach 100 genommen. Bzw habe
             // ich hier nicht wirklich den Durchschnitt je 100 Wörter.
    return sentence;
}

int words_sum(void) // Berechne die Gesamtanzahl der Words
{
    for (int i = 0; i < count_letters; i++)
    {
        if (text[i] == ' ')
        {
            words_without_beginning += 1;
        }
    }

    words = words_without_beginning + 1;
    return words;
}

int index(void)
{
    formula = round(0.0588 * L - 0.298 * S - 15.8);
    return formula;
}
