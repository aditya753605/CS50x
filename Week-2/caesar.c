#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void print_ciphertext(char *plaintext, int key, int len);

int main (int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    
    char plaintext[50];
    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';


    printf("ciphertext: ");
    int len = strlen(plaintext);

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
            if(isupper(c))
            {
                printf("%c", (c -'A' + key) % 26 + 'A');
            }
            else 
            {
                printf("%c", (c -'a' + key) % 26 + 'a');
            }
        }
        else
        {
            printf("%c", c);
        }
        
    }
    printf("\n");
    return;
}