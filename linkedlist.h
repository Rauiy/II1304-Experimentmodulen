#ifndef HEADER_FILE2
#define HEADER_FILE2

#include <stdio.h>
#include <stdlib.h>

#include "node.h"
//LinkedList priority queue
struct node *first, *last;

struct node *removeHead();
void addElement(double, int);
void printAll();
void clearAll();
#endif