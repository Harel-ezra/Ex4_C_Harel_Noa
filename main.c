#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_LETTERS ((int)26)
#define ASCI 97
/**
 * a struct for node in the tree  
 **/
typedef struct _root
{
    char letter;                         // the letter of node
    long unsigned int count;             // is for knowing  how many word have up to hear, its also mark the end of the word
    int childrenSum;                     // sum of children
    struct _root *children[NUM_LETTERS]; // array present all is children for the node
} root;

/**
 *  Function that return a new Tree node
**/
struct _root *getNewTreeNode(char c)
{
    root *node = (root *)malloc(sizeof(root));
    if (node == NULL)
    {
        return NULL;
    }
    node->letter = c;
    node->childrenSum = 0;
    node->count = 0;
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

/**
 * function to clear the dinamic memory for every node
**/
void freeDinamicMem(root *node)
{
    // make sure we dont delete this node with our clear his childern memory dinamic.
    if (node->childrenSum != 0)
    {
        for (int i = 0; i < NUM_LETTERS; i++)
        {
            if (node->children[i] != NULL)
            {
                freeDinamicMem(node->children[i]);
            }
        }
    }
    free(node);
}
/**
 * get all the word and char and insert to hear place in the tree 
 **/
void insertText(root *head)
{
    root *treeHead = head;
    root *curr = head;
    char c = fgetc(stdin);
    while (c != EOF)
    {
        if ((c <= 122 && c >= 97) || (c >= 65 && c <= 90))
        {
            c = tolower(c); // we work only with lower word
            if (curr->children[c - ASCI] == NULL)
            { // add a new node
                root *newNode = getNewTreeNode(c);
                if (newNode == NULL)
                {
                    printf("dinamic memory create is failed\n");
                    freeDinamicMem(head);
                    exit(1);
                }
                curr->children[c - ASCI] = newNode;
                curr->childrenSum++;
            }
            curr = curr->children[c - ASCI];
        }
        else if (c == ' ' || c == '\n' || c == '\t')
        {                    // end of word
            curr->count++;   // mark is end of word
            curr = treeHead; // start a new word getiing
        }
        c = fgetc(stdin);
    }
    curr->count++;
}
/** 
*   print all the word by alphabet up
**/
void printTreeUp(root *headTree, root *node, char *word, int strLen)
{
    strLen += 1;
    // save prev word up to hear
    char *prevWord = (char *)malloc(strlen(word));
    if (prevWord == NULL)
    {
        freeDinamicMem(headTree);
        printf("dinamic memory create is failed\n");
        exit(1);
    }
    strcpy(prevWord, word);
    // rellaoc for the new word
    word = realloc(word, strLen);
    if (word == NULL)
    {
        freeDinamicMem(headTree);
        free(word);
        printf("dinamic memory create is failed\n");
        exit(1);
    }
    strncat(word, &node->letter, strLen);

    if (node->count > 0)
    {
        printf("%s %ld\n", word, node->count);
    }

    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (node->children[i] != NULL)
        {
            printTreeUp(headTree, node->children[i], word, strLen);
        }
    }
    strcpy(word, prevWord);
    free(prevWord);
}

/** 
*   print all the word by alphabet down
**/
void printTreeDown(root *headTree, root *node, char *word, int strLen)
{
    strLen += 1;
    // save prev word up to hear
    char *prevWord = (char *)malloc(strlen(word)); 
    if (prevWord == NULL)
    {
        freeDinamicMem(headTree);
        printf("dinamic memory create is failed\n");
        exit(1);
    }
    strcpy(prevWord, word);

    // rellaoc for the new word
    word = realloc(word, strLen);
    if (word == NULL)
    {
        freeDinamicMem(headTree);
        free(word);
        printf("dinamic memory create is failed\n");
        exit(1);
    }
    strncat(word, &node->letter, strLen);
    for (int i = NUM_LETTERS - 1; i >= 0; i--)
    {
        if (node->children[i] != NULL)
        {
            printTreeDown(headTree, node->children[i], word, strLen);
        }
    }
    if (node->count > 0)
    {
        printf("%s %ld\n", word, node->count);
    }
    strcpy(word, prevWord);
    free(prevWord);
}

int main(int argc, char **argv)
{
    root *rootHeadTree = getNewTreeNode('\0'); // this is the truie root
    insertText(rootHeadTree);
    printf("\n");
    char *word = (char *)malloc(sizeof(char));
    word[0] = '\0';
    if (word != NULL)
    {

        if (argc > 1)
        {
            if (strcmp(argv[1], "r") == 0)
            {
                printTreeDown(rootHeadTree, rootHeadTree, word, strlen(word));
            }
        }
        else
        {
            printTreeUp(rootHeadTree, rootHeadTree, word, strlen(word));
        }
    }
    else
    {
        printf("dinamic memory create is failed\n");
    }
    freeDinamicMem(rootHeadTree);
    free(word);
    return 0;
}
