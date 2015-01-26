#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 200
#define all 0

int currentSize;

struct Node
{
	long int d_fromsource;
	long int pnodeIndex;
	long int nodeIndex;
};

struct Node heap[N+1];

void removeAll();

void updateDistance(long int index,long int d,long int p);
struct Node firstelement();
void insert(struct Node val);
struct Node removeMin();
void bubbleDown(long int index);
long int parent(long int index);
void bubbleUp(long int index);
void swap(long int index1,long int index2);
void bdown(long int index);
