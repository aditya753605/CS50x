/*a program to in which we take a 26 character key
and based on that key we make an cipher text 
of plaintext
*/
#include <stdio.h>      // printf(), fgets()
#include <ctype.h>      // isalpha(), isupper()
#include <string.h>     // strlen(), strcspn()


int valid_key(char *key);
void encryption(char *plaintext, char *key);

int main(int argc, char *argv[])
{
    // checking the number of CLI input
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *key  = argv[1];

    // checking if key is valid
    if (valid_key(key) == 0)
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    // getting plaintext fro the user
    char plaintext[256];
    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';


    printf("ciphertext: ");
    // printing ciphertext
    encryption(plaintext, key);
    printf("\n");
    return 0;
    
}
int valid_key(char *key)
{
    int len = strlen(key);
    if (len != 26)
    {
        return 0;
    }  
     for (int i = 0; i < 26; i++)
    {            
        // checking if every character is a alphabet or not
        if (!isalpha(key[i]))
        {
            return 0;
        }

        // using loop to check the repetion of a character inside the key
        for (int j = i + 1; j < 26; j++)
        {
            // using to upper incase the user typed the key case sensitive
            if (toupper(key[i]) == toupper(key[j]))
            {
                return 0;
            }
        }
    }
    return 1;
}
void encryption(char *plaintext, char *key)
{
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++)
    {
        // incase of upper case character
        if (isupper(plaintext[i]))
        {
            // gives the index of character to change it with
            int index = plaintext[i] - 'A';
            printf("%c", toupper(key[index]));
        }
        // incase of lower case character
        else if (islower(plaintext[i]))
        {
            // again gives index of char to change it with
            int index = plaintext[i] - 'a';
            printf("%c", tolower(key[index]));
        }
        // incase the typed character is not alphabet
        else
        {
            printf("%c", plaintext[i]);
        }
    }
}