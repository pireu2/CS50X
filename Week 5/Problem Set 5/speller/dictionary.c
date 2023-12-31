// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1009;

// Hash table
node *table[N];
int count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);

    node *p = table[index];
    while (p)
    {
        if (strcasecmp(p->word, word) == 0)
        {
            return true;
        }
        p = p->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        index += tolower(word[i]) * 31;
    }
    return index % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        unload();
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new = malloc(sizeof(node));
        if (!new)
        {
            unload();
            fclose(file);
            return false;
        }
        strcpy(new->word, word);
        new->next = NULL;
        unsigned int index = hash(new->word);
        if (table[index] == NULL)
        {
            table[index] = new;
            count++;
        }
        else
        {
            new->next = table[index];
            table[index] = new;
            count++;
        }
    }
    fclose(file);


    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        while (p)
        {
            node *tmp = p;
            p = p->next;
            free(tmp);
        }
        table[i] = NULL; // Set the table entry to NULL before moving to the next iteration
    }
    return true;
}
