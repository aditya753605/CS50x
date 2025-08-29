// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int word_count = 0;
// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashNum = hash(word);
    node *cursor = table[hashNum];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // read each word in the file
    char str[LENGTH + 1];
    while (fscanf(source, "%s", str) != EOF)
    {
        node *temp = malloc(sizeof(node));

        if (temp == NULL)
        {
            return false;
        }

        strcpy(temp->word, str);
        word_count++;
        int hash_Num;
        hash_Num = hash(str);

        if (table[hash_Num] == NULL)
        {
            temp->next = NULL;
        }
        else
        {
            temp->next = table[hash_Num];
        }
        table[hash_Num] = temp;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}
void freenode(node *n)
{
    if (n == NULL)
    {
        return;
    }

    freenode(n->next);

    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        freenode(table[i]);
    }
    return true;
}
