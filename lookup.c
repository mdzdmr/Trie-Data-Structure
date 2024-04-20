#include <stdio.h>
#include <string.h>
#include "trie.h"

void usage()
{
    printf("Usage: lookup [OPTION] [ARGUMENT]\n");
    printf("Options:\n");
    printf("  p <prefix>   Print all words with the given prefix\n");
    printf("  c <prefix>   Check if the prefix is in the trie\n");
    printf("  w <word>     Check if the word is in the trie\n");
    printf("  (no option)  Print all words in the trie\n");
}

int main(int argc, char* argv[])
{
    trie* t = trie_create();
    char word[256]; 
    while (scanf("%255s", word) == 1) {
        trie_insert(t, word);
    }
 
    // Processing the command-line arguments. As mentioned there are 3 arguments.
    if (argc == 1)
    {
        // Printing all words in a trie.
        trie_print(t);
    } 
    // Checking for valid options and arguments.
    else if (argc == 3) 
    { 
        // Printing all words with the given prefix.
        if (strcmp(argv[1], "p") == 0) 
        {
            trie_print_prefix(t, argv[2]);
        } 
        // Checking if the prefix is in the trie.
        else if (strcmp(argv[1], "c") == 0) 
        {
            printf("Prefix %s: %d\n", argv[2], trie_contains_prefix(t, argv[2]));
        }
        // Checking if the word is in the trie.
        else if (strcmp(argv[1], "w") == 0) 
        {
            printf("Word %s: %d\n", argv[2], trie_contains(t, argv[2]));
        } 
        // Incase of an invalid option we call the usage function and exit.
        else 
        {
            usage();
            // Freeing the trie function before exiting.
            trie_free(t); 
            return 0;
        }
    } // Incase an incorrect number of arguments provided.
    else 
    {
        // Incase of an incorrect usage.
        usage();
        // Freeing the trie before exiting.
        trie_free(t); 
        return 0;
    }
    // Freeing the trie.
    trie_free(t);
    return 0;
}
