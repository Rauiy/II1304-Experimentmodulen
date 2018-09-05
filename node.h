#ifndef NODE
#define NODE

struct node{
	double p;
	int e;
	struct node *prev; //Left
	struct node *next; //right
};
#endif
