#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int player1_score(void);
int player2_score(void);

int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; // Punktesystem definieren
string player1;
int player1_char;
string player2;
int player2_char;
int score1;
int score2;

int main(void)
{
    player1 = get_string("Player 1: "); // Abfrage der Wörter erstellen (Player1, Player2)
    player2 = get_string("Player 2: ");

    player1_char = strlen(player1);
    player2_char = strlen(player2);

    player1_score();
    player2_score();

    if (score1 == score2) // Rückgabe des Scores, wer hat gewonnen?
    {
        printf("Tie!\n");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins\n");
    }
}

int player1_score(void) // Wörter müssen im Punktsystem ausgewertet werden (Score1, Score2)
{

    score1 = 0;

    for (int i = 0; i < player1_char;
         i++) // Festlegen das die erste stelle POINTS[0] a entspricht und dann immer eins weiter
    {
        if (isupper(player1[i]))
        {
            score1 += POINTS[player1[i] - 'A'];
        }
        else if (islower(player1[i]))
        {
            score1 += POINTS[player1[i] - 'a'];
        }
    }
    return score1;
}

int player2_score(void)
{

    score2 = 0;

    for (int i = 0; i < player2_char;
         i++) // Wörter müssen im Punktsystem ausgewertet werden (Score1, Score2)
    {
        if (isupper(player2[i]))
        {
            score2 += POINTS[player2[i] - 'A'];
        }
        else if (islower(player2[i]))
        {
            score2 += POINTS[player2[i] - 'a'];
        }
    }
    return score2;
}
