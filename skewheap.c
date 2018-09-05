#include "skewheap.h"
//SkewHeap priority queue

struct node *merge(struct node *node1, struct node *node2)
{
	if (node1 == NULL)
	{
		return node2;
	}

	if (node2 == NULL)
	{
		return node1;
	}

	// 1st argument ensures priority order
	// 2nd argument ensures fifo order
	if (node1->p < node2->p || (node1->p == node2->p && node1->e < node2->e)) 
	{
		struct node *tmp = node1->next;
		node1->next = node1->prev;
		node1->prev = merge(node2, tmp);

		return node1;
	}
	else
	{
		merge(node2, node1);
	}
}

void addElementSH(double priority, int element) 
{
	struct node *new = malloc(sizeof(struct node));
	new->e = element;
	new->p = priority;
	new->next = NULL;
	new->prev = NULL;

	root = merge(root, new);
}

struct node *removeHeadSH()
{
	if (root == NULL)
		return NULL;

	struct node *tmp = root;
	
#ifdef DEBUG
	printf("SH: Getting first element\n");
#endif
	root = merge(root->prev, root->next);

	return tmp;
}

void clearAllSH()
{
	struct node *tmp = removeHeadSH();
	while(tmp != NULL)
	{	
		free(tmp);
		tmp = removeHeadSH();
	}	
}

void printNode(struct node *curr, int level)
{
	if (curr == NULL){
		return;
	}
	
	for (int i = 0; i < level; i++)
	{
		printf("  ");
	}

	printf("id:%d, prio=%lf\n", curr->e,curr->p);
	level++;
	if(curr->next != NULL)
		printNode(curr->next, level);
	if(curr->prev != NULL)
		printNode(curr->prev, level);
}

void printAllSH()
{
#ifdef DEBUG
	printf("SH: Printing all elements\n");
#endif
	struct node *tmp = root;
	printNode(tmp, 0);
}