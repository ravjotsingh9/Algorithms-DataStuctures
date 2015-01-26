#include "header.h"

struct Node firstelement(struct Node * heap, int *currentSize)
{
	return heap[1];
}

void removeAll(struct Node * heap, int * currentSize)
{
	*currentSize =0;
	memset(heap,0,(size_t)N+1);
}


void updateDistance(struct Node * heap,long int index,long int d,long int p, int *currentSize)
{
		long int i=1;
	while(i<=(*currentSize))
	{
		if(heap[i].nodeIndex == index)
		{
			heap[i].d_fromsource = d;
			heap[i].pnodeIndex = p;
			break;
		}
		i++;
	}
	bubbleUp(heap,i,currentSize);
/*	
		while(heap[i-1].d_fromsource > heap[i].d_fromsource)
		{
			swap(i-1,i);
			i = i -1;
		}
*/
}


void insert(struct Node * heap,struct Node val, int * currentSize)
{
	(*currentSize)++;
	heap[*currentSize] = val;
	bubbleUp(heap,*currentSize, currentSize);
}

struct Node removeMin(struct Node * heap,int * currentSize)
{
	struct Node tmp = heap[1];
	heap[1] = heap[*currentSize];
	(*currentSize)--;
	//bubbleDown(1);
	bdown(heap,1,currentSize);
	return tmp; 
}

void bdown(struct Node * heap,long int index,int * currentSize)
{
	if((2*index)+1 <= (*currentSize))
	{
		if(heap[(2*index)].d_fromsource < heap[(2*index)+1].d_fromsource)
		{
			swap(heap,index,(2*index),currentSize);
			bdown(heap,2*index, currentSize);
		}
		else
		{
			swap(heap,index,(2*index)+1, currentSize);
			bdown(heap,(2*index)+1, currentSize);
		}
	}
	else if((2*index)<=(*currentSize))
	{
			swap(heap,index,(2*index), currentSize);
			bdown(heap,2*index, currentSize);	
	}
}


void bubbleDown(struct Node * heap,long int index,int *currentSize)
{
	while(heap[index+1].d_fromsource < heap[index].d_fromsource)
	{
		swap(heap,index+1,index, currentSize);
		index = index +1;
	}
/*	
	if((2*index)+1 <= currentSize)
	{
		if(heap[index].d_fromsource > heap[(2*index)+1].d_fromsource)
		{
			swap(index, (2*index)+1);
			bubbleDown((2*index)+1);
			swap(index, (2*index));
			bubbleDown((2*index));
		}
		else if(heap[index].d_fromsource > heap[(2*index)].d_fromsource)
			{
				swap(index, (2*index));
				bubbleDown((2*index));
			}
		}
		else if((2*index) <= currentSize)
		{		
			if(heap[index].d_fromsource > heap[(2*index)].d_fromsource)
				{
					swap(index, (2*index));
					bubbleDown((2*index));
				}
		}*/
}

long int parent(struct Node * heap,long int index, int * currentSize)
{
	return (long int) (index/2);
}

void bubbleUp(struct Node * heap,long int index, int * currentSize)
{
		if(index <= 1)
		{
			return;
		}
		else if( heap[index].d_fromsource < heap[parent(heap,index, currentSize)].d_fromsource)
		{
			swap(heap,index,parent(heap,index, currentSize), currentSize);
			index = parent(heap,index, currentSize);
			bubbleUp(heap,index,currentSize);
		}
/*
		while(heap[index-1].d_fromsource > heap[index].d_fromsource)
		{
			swap(heap,index-1,index, currentSize);
			index = index -1;
		}
*/
}

void swap(struct Node *heap,long int index1,long int index2, int * currentSize)
{
	struct Node tmp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = tmp;
}
