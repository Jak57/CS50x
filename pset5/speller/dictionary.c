// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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

// Number of buckets in hash table
const unsigned int N = 143093, mod = 143093;

//Array of powers
long long power[46];
int count = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_value = hash(word);
    node *list = table[hash_value];

    // Checking if list NULL or not
    if (list != NULL)
    {
        // Iterating through linked list
        for (node *tmp = list; tmp != NULL; tmp = tmp->next)
        {
            // Checking for matching string
            if (strcasecmp(tmp->word, word) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Variables
    int i, n;
    n = strlen(word);
    long long hash_value = 0, val;

    // Iterating through string and calculating hash
    for (i = 0; i < n; i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            val = word[i] - 'a' + 1;
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            val = word[i] - 'A' + 1;
        }
        else if (word[i] == '\'')
        {
            val = 27;
        }

        hash_value = (hash_value + (val * power[i + 1])) % mod;
    }

    hash_value = (unsigned int) hash_value;
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char st[LENGTH + 1];
    int i, p = 31;
    unsigned int hash_value;

    node *n = NULL;
    power[1] = 1;

    // Calculating powers
    for (i = 2; i <= 45; i++)
    {
        power[i] = (power[i - 1] * p) % mod;
    }

    // Opening file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    
    // Loading dictionary
    while (fscanf(file, "%s", st) != EOF)
    {
        hash_value = hash(st);
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        
        // Copying string
        strcpy(n->word, st);
        n->next = NULL;

        // Building hash table
        if (table[hash_value] == NULL)
        {
            table[hash_value] = n;
        }
        else
        {
            n->next = table[hash_value];
            table[hash_value] = n;
        }
       
        count++;
    }
    
    // Closing file
    fclose(file);
   

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count - 1;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *list = NULL;
    // Iterating through table and freeing memory
    for (int i = 0; i < N; i++)
    {
        list = table[i];
        
        while (list != NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    
    return true;
}
