/*
	To run use the makefile and "make all"
	Or
	First compile skew heap and linked list to objects
		gcc linkedlist.c -c -o linkedlist.o 
		gcc skewheap.c -c -o skewheap.o 
	Second compile the experiment using skew heap and linked list objects
		gcc experiment.c linkedlist.o skewheap.o -o exp 
		
	Then either run experiment with or without arguments. However, latter arguments requires former arguments to be assigned
		./exp max min n
		where 
			max -> maximum number of elements to run / Default=10000
			min -> minumim number of elements, also the increment size for the test / Default=10
			n 	-> specifik test case to run / Default=unassigned -> runs all testcases
				1 -> general-case
				2 -> worst-case doubly linked list
				3 -> worst-case skew heap
		note the combination max=10000 & min=10 triggers a special run time, where the tests are incremented with *10.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "skewheap.h"
#include "linkedlist.h"

// 0 = put, 1 = get
int *operations;
int *values;

void reset()
{
#ifdef DEBUG
	printf("Freeing allocated data\n");
#endif
	clearAll();
	clearAllSH();
}

int init = 1;

// e = experiment number
// n = number of puts to generate (equally amount of get will be generated
void initiator(int e, int n)
{
	if(init)
	{
		// Initiate arrays first time used
		operations = malloc(4*n*2);
		values = malloc(4*n*2); // Only half is used for experiment 2 and 3
		init = 0;
	}
	
	if(e == 1)
	{
		
	
		int puts = 0, gets = 0;
		for(int i = 0; i < n*2; i++)
		{
			if(puts > n)
			{
				operations[i] = 1;
				values[i] = 0; // Doesn't matter we do not check the value to be correct...
				gets++;
			}
			else if(gets > n || puts == gets) // If they are the same we must put anything to be able to get something
			{
				operations[i] = 0;
				values[i] = rand()%n; // Max priority = number of a single operation, increases the chance of collisions
				puts++;
			}
			else
			{
				operations[i] = rand()%2;
				if(operations[i])
				{	// Get operation
					values[i] = 0;
					gets++;
				}
				else 
				{
					// Put operation
					values[i] = rand()%n; // Max priority = number of a single operation, increases the chance of collisions
					puts++;
				}
			}
		}
		return;
	}
	// experiment 2 and 3 has the same order or operations, its the priority order that changes
	for(int i = 0; i < n; i++)
	{
		operations[i] = 0; // Start with puts
		operations[i+n] = 1;	// Ends with gets
	}
	
	if(e == 2) // Linkedlist worst case
	{
		int c = 0;
		int m = n;
		for(int i = 0; i < n; i++)
		{
			if(i%2==0) 
			{
				values[i] = c;
				c++;
			}
			else 
			{
				values[i] = m;
				m--;
			}
		}
	}
	else if(e == 3) // Skewheap worst case
	{		
		for(int i = 0; i < n; i++)
		{
			values[i] = i; 
		}
	}
}

void experimentLL(int n)
{
	for(int i = 0; i < n*2; i++)
	{
		if(operations[i])
		{
			struct node *tmp= removeHead();
			if(tmp != NULL)
				free(tmp);
		}
		else
		{
			addElement(values[i],i);
		}
	}
}

void experimentLLPut(int n)
{
	for(int i = 0; i < n; i++)
	{
		addElement(values[i],i);
	}
}

void experimentLLGet(int n)
{
	for(int i = 0; i < n; i++)
	{
		struct node *tmp= removeHead();
		if(tmp != NULL)
			free(tmp);
	}
}

void experimentSH(int n)
{
	for(int i = 0; i < n*2; i++)
	{
		if(operations[i])
		{
			struct node *tmp = removeHeadSH();
			if(tmp != NULL)
				free(tmp);
		}
		else
		{
			addElementSH(values[i],i);
		}
	}
}

void experimentSHPut(int n)
{
	for(int i = 0; i < n; i++)
	{
		addElementSH(values[i],i);
	}
}

void experimentSHGet(int n)
{
	for(int i = 0; i < n; i++)
	{
		struct node *tmp = removeHeadSH();
		if(tmp != NULL)
			free(tmp);
	}
}

void printResultExp(double times[], int n, int r)
{
	double sum = 0;
	for(int i = 0; i < n; i++)
	{
		sum += times[i];
	}
	
	sum = sum / n;
	
	printf("%d\t%lf\t%d\n", r, sum, n);
}

void printResultExp2(double times[], double times2[], int n, int r)
{
	double sum = 0, sum2 = 0;
	for(int i = 0; i < n; i++)
	{
		sum += times[i];
		sum2 += times2[i];
	}
	
	sum = sum / n;
	sum2 = sum2/n;
	
	printf("%d\t%lf\t%lf\t%d\n", r, sum, sum2, n);
}

int max = 10000, min = 10, c = 100;

void startExperiment(int alt)
{
	int i = min;
	struct timeval start;
	struct timeval end;
	double times[2][c];
	double times2[2][c];
	
	if (alt == 1)
		printf("type\telements\ttime\truns\n");
	else
		printf("type\telements\tputtime\tgettime\truns\n");
	while(i<=max)
	{		
		if(alt == 1)
		{
			for(int j = 0; j < c; j++)
			{	
				initiator(alt, i); // New each run to maintain randomness
				reset();
				gettimeofday(&start, NULL);
				experimentLL(i);
				gettimeofday(&end, NULL);
				times[0][j] = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
				
				gettimeofday(&start, NULL);
				experimentSH(i);
				gettimeofday(&end, NULL);
				times[1][j] = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
			}
		
			printf("LinkedList\t");
			printResultExp(times[0], c, i);
			
			printf("Skewheap\t");
			printResultExp(times[1], c, i);
		}
		else 
		{
			initiator(alt, i); // New once
			for(int j = 0; j < c; j++)
			{	
				reset(); // make sure linked list is empty
				gettimeofday(&start, NULL); // Measure executed time for put on linked list
				experimentLLPut(i);
				gettimeofday(&end, NULL);
				times[0][j] = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
				
				gettimeofday(&start, NULL); // Measure executed time for get on linked list
				experimentLLGet(i);
				gettimeofday(&end, NULL);
				times2[0][j] = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
				
				reset(); // Make sure skew heap is empty
				gettimeofday(&start, NULL); // Measure executed time for put on skew heap 
				experimentSHPut(i);
				gettimeofday(&end, NULL);
				times[1][j] = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
				
				gettimeofday(&start, NULL); // Measure executed time for get on skew heap
				experimentSHGet(i);
				gettimeofday(&end, NULL);
				times2[1][j] = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
			}
			
			printf("LinkedList\t");
			printResultExp2(times[0], times2[0], c, i);
			
			printf("Skewheap\t");
			printResultExp2(times[1], times2[1], c, i);
		}
		if(max == 10000 && min == 10)
			i = i*10;
		else 
			i += min;
	}
}


int main(int argc, char *argv[])
{

	int alt = 0;
	if(argc > 1)
	{
		max = atoi(argv[1]);
	}
	if(argc > 2)
	{
		min = atoi(argv[2]);
	}
	if(argc > 3)
	{
		alt = atoi(argv[3]);
	}
	srand(time(NULL));
	// TODO: initiate and make experiment1
	initiator(1, max); // Initate array sizes
	
	if(alt)
	{
		startExperiment(alt);
	}
	else
	{
		startExperiment(1);
		startExperiment(2);
		startExperiment(3);
	}
	return 0;
}