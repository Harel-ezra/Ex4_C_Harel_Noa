#ifndef _main_H_
#define _main_H_

/**
 * a node struct
 **/
typedef struct _root root;

/**
 * create a node struct
 **/
struct _root *getNewTreeNode(char c);

/**
 * function to clear the dinamic memory for every node
**/
void freeDinamicMem(root *node);

/**
 * get all the word and char and insert to hear place in the tree 
 **/

void insertText(root *head);

/** 
*   print all the word by alphabet up
**/

void printTreeUp(root *headTree, root *node, char *prevWord);

/** 
*   print all the word by alphabet down
**/

void printTreeDown(root *headTree, root *node, char *prevWord);

/**
 *  main progrem
 **/

int main(int argc, char **argv);

#endif