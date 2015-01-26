#include"header.h"

void initializeheap()
{
	currentSize = 0;
}

void main()
{
	initializeheap();	
	struct Node	tmp;
	tmp.d_fromsource = 10;
	tmp.nodeIndex = 1;
	insert(tmp);
	tmp.d_fromsource = 13;
	tmp.nodeIndex = 2;
	insert(tmp);
	tmp.d_fromsource = 100;
	tmp.nodeIndex = 3;
	insert(tmp);
	tmp.d_fromsource = 1054;
	tmp.nodeIndex = 4;
	insert(tmp);
	tmp.d_fromsource = 1000;
	tmp.nodeIndex = 5;
	insert(tmp);
	tmp.d_fromsource = 2;
	tmp.nodeIndex = 6;
	insert(tmp);
	printf("Removed:%ld",removeMin().d_fromsource);
	updateDistance(1,500,1);
	printf("Removed:%ld",removeMin().d_fromsource);

}
