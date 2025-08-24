/* a program to perform like a game of scrabble 
wherre we take two input and calculate their score 
based on the input and display the winner
*/


#include <ctype.h>      // isupper(), islower()
#include <stdio.h>      // printf(), fgets()
#include <string.h>     // strcspn() function

// Declaring a constant array for points
const int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1,
                      3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// max lenght for input
#define max_lenght 50

int compute_score(char* word);

int main(void)
{
    char word1[max_lenght], word2[max_lenght];

    // getting input for player 1
    printf("Player 1: ");
    fgets(word1, sizeof(word1), stdin);

    // removing next line from the input
    word1[strcspn(word1, "\n")] = '\0';

    // getting input for player 2
    printf("Player 2: ");
    fgets(word2, sizeof(word2), stdin);

    // removing next line
    word2[strcspn(word2, "\n")] = '\0';

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // displaying output
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    return 0;
}

int compute_score(char *word)
{

    int score = 0;
    int len = strlen(word);
    for(int i = 0; i < len; i++)
    {
        // computing for uppercasse letter
        if(isupper(word[i]))
        {
            score = score + points[word[i] - 'A'];
        }

        // computing for lowercase letter
        else if (islower(word[i]))
        {
            score = score + points[word[i] - 'a'];
        }
    }
    return score;
}