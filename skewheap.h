#ifndef HEADER_FILE1
#define HEADER_FILE1

#include <stdio.h>
#include <stdlib.h>

#include "node.h"
//Skewheap priority queue
struct node *root;

struct node *merge(struct node *, struct node *);
struct node *removeHeadSH(); // Get
void addElementSH(double, int); // Put
void printAllSH();
void printNode(struct node *, int);
void clearAllSH();
#endif