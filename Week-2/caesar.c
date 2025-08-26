/* a program to take a command line argument (key), and input 
from the user and convert it into cipher message
*/ 
#include <stdio.h>      // printf(), fgets()
#include <ctype.h>      // isalpha(), isdigit(), isupper()
#include <stdlib.h>     // atoi()
#include <string.h>     // strlen()

void print_ciphertext(char *plaintext, int key, int len);

// taking command-line argument
int main (int argc, char **argv)
{
    // checking number of CLI
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // checking if the input is number or not
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    
    // getting text from user
    char plaintext[50];
    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    
    printf("ciphertext: ");
    int len = strlen(plaintext);

    // printing ciphertext
    print_ciphertext(plaintext, key, len);
    return 0;
}

void print_ciphertext(char *plaintext, int key, int len)
{
    for(int i = 0; i < len; i++)
    {
        char c = plaintext[i];

        if(isalpha(c))
        {
            // converting uppercase alphabet to cipher text
            if(isupper(c))
            {
                printf("%c", (c -'A' + key) % 26 + 'A');
            }
            // converting lowercase alphabet
            else 
            {
                printf("%c", (c -'a' + key) % 26 + 'a');
            }
        }
        // if it is a symbol it remains same
        else
        {
            printf("%c", c);
        }
        
    }
    printf("\n");
    return;
}
