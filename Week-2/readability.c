/*a program to calculate the grade 
of the student according to the 
sentences that he can read.
*/

#include <ctype.h>      // isalpha()
#include <math.h>       // round()
#include <stdio.h>      // printf(), fgets()
#include <string.h>     // strlen(), strcspn()

int count_letters(char* text, int len);
int count_words(char* text, int len);
int count_sentences(char* text, int len);

int main()
{
    // getting text input from user
    char text[500];
    printf("Text: ");
    fgets(text, sizeof(text), stdin);
    // deleting next line if any
    text[strcspn(text, "\n")] = '\0';

    int len = strlen(text);

    // getting number of letter, words, sentences respectively
    int letters = count_letters(text,len);

    int words = count_words(text, len);

    int sentences = count_sentences(text, len);

    // calculating L and S for Coleman-Liau index
    float L = (letters/ (float) words) * 100;
    float S = (sentences/ (float) words) *100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // printing grade(output)
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
    return 0;
}

int count_letters(char* text, int len)
{
    int count = 0;

    for (int i = 0; i < len; i++)
    {
        if(isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(char* text, int len)
{
    int count = 0;

    for(int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count + 1;
}

int count_sentences(char* text, int len)
{
    int count = 0;

    for(int i = 0; i < len; i++)
    {
        if(text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
       
    }
    return count;
}