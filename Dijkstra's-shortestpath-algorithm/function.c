#include "header.h"

struct Node firstelement()
{
	return heap[1];
}

void removeAll()
{
	currentSize =0;
	memset(heap,0,(size_t)N+1);
}


void updateDistance(long int index,long int d,long int p)
{
		long int i=1;
	while(i<=currentSize)
	{
		if(heap[i].nodeIndex == index)
		{
			heap[i].d_fromsource = d;
			heap[i].pnodeIndex = p;
			break;
		}
		i++;
	}
	//bubbleUp(i);	
		while(heap[i-1].d_fromsource > heap[i].d_fromsource)
		{
			swap(i-1,i);
			i = i -1;
		}

}


void insert(struct Node val)
{
	currentSize++;
	heap[currentSize] = val;
	bubbleUp(currentSize);
}

struct Node removeMin()
{
	struct Node tmp = heap[1];
	heap[1] = heap[currentSize];
	currentSize--;
	//bubbleDown(1);
	bdown(1);
	return tmp; 
}

void bdown(long int index)
{
	if((2*index)+1 <= currentSize)
	{
		if(heap[(2*index)].d_fromsource < heap[(2*index)+1].d_fromsource)
		{
			swap(index,(2*index));
			bdown(2*index);
		}
		else
		{
			swap(index,(2*index)+1);
			bdown((2*index)+1);
		}
	}
	else if((2*index)<=currentSize)
	{
			swap(index,(2*index));
			bdown(2*index);	
	}
}


void bubbleDown(long int index)
{
	while(heap[index+1].d_fromsource < heap[index].d_fromsource)
	{
		swap(index+1,index);
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

long int parent(long int index)
{
	return (long int) (index/2);
}

void bubbleUp(long int index)
{
		if(index == 0)
		{
			return;
		}
		while( heap[index].d_fromsource < heap[parent(index)].d_fromsource)
		{
			swap(index,parent(index));
			index = parent(index);
		}
		while(heap[index-1].d_fromsource > heap[index].d_fromsource)
		{
			swap(index-1,index);
			index = index -1;
		}
}

void swap(long int index1,long int index2)
{
	struct Node tmp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = tmp;
}
