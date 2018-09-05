#include "linkedlist.h"
//LinkedList priority queue

// Put
void addElement(double priority, int element)
{
	struct node *new = malloc(sizeof(struct node));
	new->p = priority;
	new->e = element;
	new->prev = NULL;
	new->next = NULL;
	
	if(first == NULL)
	{
		first = last = new;
	}
	else
	{
		double sum = (first->p + last->p)/2;
		if(priority < sum)
		{
#ifdef DEBUG 
			printf("LL: Adding from the front\n");
#endif
			//start from front
			struct node * tmp = first; 
			
			while(tmp != NULL)
			{
				// Only put more prioritized in front
				if(priority < tmp->p)
				{
					struct node * prv = tmp->prev;
					
					if(prv != NULL)
					{
						prv->next = new;
						new->prev = prv;
					}
					else
					{
						first = new;
					}
					
					new->next = tmp;
					tmp->prev = new;
					break;
				}
				tmp = tmp->next;
			}
		}
		else{
		
#ifdef DEBUG 
			printf("LL: Adding from the back\n");
#endif
			// start from back
			// puts less prioritized or equal at behind
			struct node * tmp = last; 
			
			while(tmp != NULL)
			{
				
				if(priority >= tmp->p )
				{
					struct node * nxt = tmp->next;
					
					if(nxt != NULL)
					{
						new->next = nxt;
						nxt->prev = new;
					}
					else
					{
						last = new;
					}
					
					tmp->next = new;
					new->prev = tmp;
					break;
				}
				tmp = tmp->prev;
			}
		}
	}
}

// Get
struct node *removeHead()
{
	if (first == NULL)
		return NULL;
	
#ifdef DEBUG
	printf("LL: Getting first element\n");
#endif

	struct node * tmp = first; 

	if (first == last)
	{
		first = NULL;
		last = NULL;
	}
	else
	{
		first = first->next;
		first->prev = NULL;
	}
	
	return tmp;
}

void clearAll()
{
	struct node *tmp = removeHead();
	while(tmp != NULL)
	{
		
		free(tmp);
		tmp = removeHead();
	}
}

void printAll()
{
#ifdef DEBUG
	printf("LL: Printing all elements\n");
#endif
	struct node *tmp = first;
	int i = 0;
	while (tmp != NULL) 
	{
		printf("%d. id:%d, prio=%lf\n", i++, tmp->e,tmp->p);
		tmp = tmp->next;
	}
}