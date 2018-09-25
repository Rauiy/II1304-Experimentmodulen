/*
	To run the validating tests use the makefile to compile 
		make all
		make alld
			alld compiles into debug mode, which makes the test print out additional information
	Or
	First compile skew heap and linked list to objects with or without debug flag
		gcc linkedlist.c -c -o linkedlist.o 
		gcc skewheap.c -c -o skewheap.o 
	Second compile the test using skew heap and linked list objects with or without debug flag
		gcc test.c linkedlist.o skewheap.o -o test 
	To run in debug mode where additional information are provided during run, add the debug flag to any compilation
		"compile command" -D DEBUG
		
	Then run the tests 
		./test
			The test then notifies if the datastructures failed or succeded the tests 
			Upon failure the test will also provide which datastructure failed at which part
*/
#include <stdio.h>
#include <stdlib.h>

#include "skewheap.h"
#include "linkedlist.h"

int test1[] = {4177, 1759, 2383, 1489, 10091, 8209, 8221, 14159, 8221, 1759}; // Priority sequence
int test2s1[] = {1489, 1759, 1759, 2383, 4177, 8209, 8221, 8221, 10091, 14159}; // Priority sequence
int test2s2[] = {4,2,10,3,1,6,7,9,5,8}; // Element sequence
// 0 = put, 1 = get
int test3s1[] = {0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1}; // Operation sequence
int test3s2[] = {1759, 1, 2383, 1489, 4, 1759, 2153, 2161, 6, 7, 8, 17, 12, 3}; // Expected element/Inserted priority

void printResult(int test, int res)
{
	if(res > 0)
	{
		if(res == 1)
		{
			printf("Test%d: Linked List failed in middle of test due wrong order\n", test);
		}
		else if(res == 10)
		{
			printf("Test%d: Skew Heap failed in middle of test due wrong order\n", test);
		}
		else if(res == 11)
		{
			printf("Test%d: Both datastructure failed in middle of test due wrong order\n", test);
		}
	}
	else 
	{
		printf("Test%d: Both data structures was approved\n", test);
	}
}

void reset()
{
	printf("Freeing allocated data\n");
	struct node *tmp = removeHead();
	while(tmp != NULL)
	{
		
		free(tmp);
		tmp = removeHead();
	}

	tmp = removeHeadSH();
	while(tmp != NULL)
	{	
		free(tmp);
		tmp = removeHeadSH();
	}	
}

int main(int argc, char *argv[])
{
	// First test, testing put, no erros = successs
	printf("Test1 (Inserting elements): Starting\n");
	int i;
	for(i = 0; i < 10; i++)
	{
		addElementSH(test1[i],i+1);
		addElement(test1[i],i+1);
	}
#ifdef DEBUG
	printAll();
	printf("\n");
	printAllSH();
#endif	
	printResult(1, 0);
	
	
	printf("\n");
	printf("Test2 (Removing elements): Starting\n");
	// Second test, testing get, no errors and right sequence = successs
	struct node *ll, *sh;
	int res = 0;
	for(i = 0; i < 10; i++)
	{
		ll = removeHead();
		sh = removeHeadSH();
		
#ifdef DEBUG
		printf("Expected: %d->%d\n", test2s2[i], test2s1[i]);
		printf("ll: %d->%l\n", ll->e, ll->p);
		printf("sh: %d->%l\n", sh->e, sh->p);
		printf("\n");
#endif		
		if(ll->e != test2s2[i] || ll->p != test2s1[i])
		{
			res += 1;
		}
		
		if(sh->e != test2s2[i] || sh->p != test2s1[i])
		{
			res += 10;
		}
		
		free(ll);
		free(sh);
		
		if(res > 0)
		{
			printResult(2, res);
			reset();
			return 0;
		}
	}
	printResult(2, res);
	
	// Third test
	res = 0;
	printf("\n");
	printf("Test3 (Mix): Starting\n");
	for(i = 0; i < 10; i++)
	{
		if(test3s1[i])
		{
			ll = removeHead();
			sh = removeHeadSH();
			
#ifdef DEBUG
			printf("Test3: Removed\n");
			printf("ll: %d->%l\n", ll->e, ll->p);
			printf("sh: %d->%l\n", sh->e, sh->p);
			printf("\n");
#endif	
			
			if(ll->e != test3s2[i])
			{
				res += 1;
			}
			
			if(sh->e != test3s2[i])
			{
				res += 10;
			}
	
			free(ll);
			free(sh);
		
			if(res > 0)
			{
				printResult(3, res);
				reset();
				return 0;
			}
		}
		else
		{
			addElement(test3s2[i],i+1);
			addElementSH(test3s2[i],i+1);
			
#ifdef DEBUG
			printf("Test3: Added %d:%d\n", i+1, test3s2[i]);
			printAll();
			printf("\n");
			printAllSH();
			printf("\n");
#endif	
		}
	}
	printResult(3, res);
	
	return 0;
}