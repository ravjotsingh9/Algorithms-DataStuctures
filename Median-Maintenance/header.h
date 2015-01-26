#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10000

int min_currentSize;
int max_currentSize;

struct Node
{
	long int d_fromsource;
	long int pnodeIndex;
	long int nodeIndex;
};

struct Node minheap[N+1];
struct Node maxheap[N+1];

void removeAll(struct Node *heap, int * currentSize);

void updateDistance(struct Node *heap,long int index,long int d,long int p,int * currentSize);
struct Node firstelement(struct Node * heap,int * currentSize);
void insert(struct Node * heap,struct Node val,int * currentSize);
struct Node removeMin(struct Node * heap, int * currentSize);
void bubbleDown(struct Node * heap,long int index,int * currentSize);
long int parent(struct Node * heap,long int index,int * currentSize);
void bubbleUp(struct Node * heap,long int index,int * currentSize);
void swap(struct Node * heap,long int index1,long int index2, int * currentSize);
void bdown(struct Node * heap,long int index, int * currentSize);
