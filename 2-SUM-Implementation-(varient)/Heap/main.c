#include "header.h"

long int readfile(char *inputfile,struct Node * maxh, struct Node * minh)
{
	char line[80];
	FILE *file;
	file = fopen(inputfile,"r");
	printf("%s","Starting reading file ");	
	unsigned int counter = 0;
	fgets(line,80, file);
	char v[20];
	strcpy(v,line);
	int value = atoi(v);
	long int median = value;
	long int som = median;
	struct Node tmp;
	tmp.d_fromsource = value;
	insert(minh,tmp,&min_currentSize);
	while(fgets(line,80, file))
	{
		if(counter%1000 == 0)
		{
			printf("*");	
//			printf("%ld ",median);	
			fflush(stdout);
		}
		char *ch;
		char v[20];
		strcpy(v,line);
		ch = &(v[strlen(v)]);
		int val = atoi(v);
		if(val > median)
		{
			struct Node tmp;
			tmp.d_fromsource = val;
			insert(minh,tmp,&min_currentSize);
		}
		else
		{
			val = 0-val;
			struct Node tmp;
			tmp.d_fromsource = val;
			insert(maxh,tmp,&max_currentSize);
		}

		while (max_currentSize - min_currentSize > 1 )
		{
			int val = 0 - (removeMin(maxh,&max_currentSize).d_fromsource);
			struct Node tmp;
			tmp.d_fromsource = val;
			insert(minh,tmp,&min_currentSize);
		}
		while(max_currentSize - min_currentSize < -1)
		{
			int val = removeMin(minh,&min_currentSize).d_fromsource;
			val = 0-val;
			struct Node tmp;
			tmp.d_fromsource = val;
			insert(maxh,tmp,&max_currentSize);
		}
		if(max_currentSize == min_currentSize)
		{
			median = 0 - (firstelement(maxh,&max_currentSize).d_fromsource);
		}
		else if(max_currentSize - min_currentSize == 1)
		{
			median = 0 - (firstelement(maxh,&max_currentSize).d_fromsource);
		}
		else if(min_currentSize - max_currentSize == 1)
		{	
			median = firstelement(minh,&min_currentSize).d_fromsource;
		}
		som = som + median;
		counter++;
		memset(line,0,80);
//		print();
	}
	printf("Done Reading\n");
	fclose(file);
	return som;
}

print()
{
	int i =1;
	while(i<= max_currentSize)
	{
		printf("%ld ",maxheap[i].d_fromsource);
		i++;
	}
	printf("\n");
	i =1;
	while(i<= min_currentSize)
	{
		printf("%ld ",minheap[i].d_fromsource);
		i++;
	}
	printf("\n");
}
int main(int argc, char **argv)
{
	long int som = readfile(argv[1],maxheap, minheap);
	printf("(Sum of Medians)%10000 : %ld",som%10000);
	return 0;
}
