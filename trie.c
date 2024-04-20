#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

trie_node* find_node_for_string(trie* t, char* str);
void trienode_free(trie_node* node);

// Creates a new trie node
trie_node* trienode_create(char data)
{
    // Dynamically allocating memory for a new node.
    trie_node* node = (trie_node*)malloc(sizeof(trie_node));
    // Setting the nodes character to the provided data.
    node->data = data;
    // Initializes the word pointer to null.
    node->word = NULL;
    // Iterating through to make all children pointers to NULL.
    for (int i = 0; i < ALPHABET_SIZE; i++) 
    {
        node->children[i] = NULL;
    }
    // Returning the created node.
    return node;
}

// Creates a new trie
trie* trie_create()
{
    // Dynamically allocates memory for a new trie.
    trie* t = (trie*)malloc(sizeof(trie));
    // Createing the root node with '$' to mark the root.
    t->root = trienode_create('$'); 
    // Initializing the size of the trie as 0.
    t->size = 0;
    // Returning the created trie.
    return t;
}

// Inserts a word into the trie, if it doesn't already exist
void trie_insert(trie* t, char* word)
{
    // Step 1: We create a pointer variable to a trie_node that represents the current node in the trie
    // and initialize it to the root node.
    trie_node* current = t->root;
    // Step 2: We create a pointer variable to char that points at the first character of the word.
    char* original_word = word; 
    // Step 3: Iterating through the word
    while (*word != '\0') {
        // Calculating the index of the character in the children array.
        int index = *word - 'a'; 
        // Checking if the current node has a child at the index because if it doesn't then we create
        // a new node at this index for the given character using trienode_create.
        if (current->children[index] == NULL) 
        {
            current->children[index] = trienode_create(*word);
        }
        // Descending down to the child node.
        current = current->children[index]; 
        // Moving to the next character in the word.
        word++; 
    }
    // Step 4: After all characters are processed
    if (current->word == NULL) {
        // We duplicate the word using strdup and store it in the node.
        current->word = strdup(original_word); 
        // Incrementing the size of the trie.
        t->size++; 
    }
}

// Checks if a word is present in the trie. Using a helper method as suggested in the assignment.
int trie_contains(trie* t, char* word)
{
    // Finds the node corresponding to the last character of the word.
    trie_node* node = find_node_for_string(t, word);
    // Returning true if the node is found and it marks the end of a word.
    return node != NULL && node->word != NULL;
}

// Checks if a given prefix is present in the trie
int trie_contains_prefix(trie* t, char* prefix)
{
    // Returns true if the prefix is found in the trie.
    return find_node_for_string(t, prefix) != NULL;
}
 
trie_node* find_node_for_string(trie* t, char* str) 
{
    // Starting traversal from the root.
    trie_node* currentNode = t -> root;
    // Looping until the end of the string or until a NULL node is encountered.
    while (*str != '\0' && currentNode != NULL) 
    {
        // Calculating the index of the character.
        int i = *str - 'a';
        // Moving to the corresponding child node.
        currentNode = currentNode -> children[i];
        // Moving to the next character.
        str++;
    }
    // Returning the node at the end of the traversal.
    return currentNode;
}

// Recursively prints all words in a trie starting from the given node (asc. order).
void trienode_print(trie_node* node)
{
    // Checking if the node marks the end of a word and then printing.
    if (node->word != NULL) 
    {
        printf("%s\n", node -> word);
    }
    // Looping through all possible children.
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        // If the child exists then recursively printing the subtree.
        if (node->children[i] != NULL) 
        {
            trienode_print(node->children[i]);
        }
    }
}

// Recursively prints all words in a trie starting from the root node (asc. order).
void trie_print(trie* t)
{
    // Recursively printing the root.
    trienode_print(t->root);
}

// Recursively prints all words in the given trie that begin with the given prefix (asc. order).
void trie_print_prefix(trie* t, char* prefix)
{
    // Finding the node for the given prefix.
    trie_node* node = find_node_for_string(t, prefix);
    
    // Printing all words starting from the found node and nothing otherwsise.
    if (node != NULL) 
    {
        trienode_print(node);
    }
}

// Frees all memory allocated for the given trie. Using a helper method as suggested in the assignment.
void trie_free(trie* t)
{
    // Freeing all nodes starting from the root.
    trienode_free(t->root);
    // Freeing the trie structure.
    free(t);
}

// Helper method for trie_free
void trienode_free(trie_node* node) 
{
    // Looping through all children and if a child exists then we recursively 
    // free the subtree rooted at the child.
    for (int i = 0; i < ALPHABET_SIZE; i++) 
    {
        if (node->children[i] != NULL) 
        {
            trienode_free(node->children[i]);
        }
    }
    // Freeing the dynamically allocated word.
    free(node->word);
    // Freeing the node itself.
    free(node);
}

