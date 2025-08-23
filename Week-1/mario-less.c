// making a program to print a pattern like this
//         #
//        ##
//       ###

#include <ctype.h>      // for isdigit()
#include <stdio.h>      // for printf(), scanf()
#include <stdlib.h>     // for atoi()
#include <string.h>     // for strlen()

// function to print a single row of pyramid
void print_pattern(int bricks, int spaces);

int main()
{
    
    int height, valid ;
    char check[25];

    // Prompt until user enters a valid height (1–8)
    do
    {
        printf("Height: ");
        scanf("%s", check);
        valid = 1;

        // Check if all characters in input are digits
        int len = strlen(check);
        for (int i = 0; i < len; i++)
        {
            
            if (!isdigit(check[i]))
            {
                valid = 0;
                break;
            }
        }
        
        if (valid)
        {
            height = atoi(check);    // Convert to integer if input is valid
        }
        
        else
        {/ Force reprompt on invalid input
            height = 0;        /
        }
    }
    while (height < 1 || height > 8);
    
    // printing pyramid
    for (int i = 1; i <= height; i++)
    {
        print_pattern(i, height);
    }
    return 0;
}

void print_pattern(int bricks, int spaces)
{
    // loop to print blank space 
    for (int i = bricks; i < spaces; i++)
    {
        printf(" ");
    }

    // loop to print bricks
    for(int i = 0; i < bricks; i++)
    {
        printf("#");
    }

    printf("\n");
    return;
}