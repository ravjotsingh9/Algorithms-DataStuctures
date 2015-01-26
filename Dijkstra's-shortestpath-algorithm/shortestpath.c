#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"
//#define N 200



struct node
{
	long int nodeNum;
	long int cost;
	struct node * next;
};
struct node * adjacencyList[N+1];

struct Detail
{
	long int visited;
	long  int shortestdistance;
	long int viaNode; 
};

struct Detail detail[N+1];

/* to print entire adjacency matrix: might take a long time*/
void printAdjacency()
{
	long int i=1;
	printf("%s\n","Printing:");	
					fflush(stdout);	
	while(i<= N)
	{
		printf("%ld\t", i);
					fflush(stdout);	
		if(adjacencyList[i]!= NULL)
		{
			struct node * j =adjacencyList[i];
			while(j != NULL)
			{
				printf("%ld,%ld\t", j->nodeNum,j->cost);
					fflush(stdout);	
				j = j->next;
			}
		}
		printf("\n");
		i++;
	}
	printf("%s\n","Printed!!");	
}


/* free memory: used while free-ing graph memory */
void memfree(struct node * ptr)
{
	if(ptr!=NULL)
	{
		ptr = ptr->next;
		memfree(ptr);
	}
	else
	{
		free(ptr);
		ptr = NULL;
	}
}

/* free graph memory */
void freegraph()
{
	printf("%s\n","Starting free-ing the memory:");	
	long int i=1;
	while(i<=N)
	{
		if(i%10000 == 0)
		{
			printf("#");
			fflush(stdout);	
		}
		if(adjacencyList[i]!= NULL)
		{
			memfree(adjacencyList[i]);
		}
		adjacencyList[i]=NULL;
		i++;
	}
	printf("%s\n","Free-ed!!");	
}

void create_adjacency(char * inputfile)
{
	char line[1024];
	FILE *file;
	file = fopen(inputfile,"r");
	printf("%s","Starting reading file ");	
			fflush(stdout);
	long int counter = 1;
	while(fgets(line,1024, file))
	{
		if(counter%1 == 0)
		{
			printf("*");	
			fflush(stdout);
		}
		char *ch;
		char to[20], n[20], c[20],count[20];
		unsigned int nn = 1;
		unsigned int cost = 1;
		ch = strtok(line,"\t");
		strcpy(count,ch);
		counter = atol(count);
//		ch = strtok(NULL,"\t");
			ch = strtok(NULL, ",");
		while(ch!=NULL && *ch!='\r' && *ch!='\n')
		{
//			char * chr;
//			strcpy(to,ch);
			strcpy(n,ch);
//			printf("%s,",n);
			nn = atol(n);
			ch = strtok(NULL, "\t");
			strcpy(c,ch);
//			printf("%s\t",c);
			cost = atol(c);
			struct node * tmp = (struct node *) malloc(sizeof(struct node));
			tmp->nodeNum = nn;
			tmp->cost = cost;
			tmp->next = adjacencyList[counter];
			adjacencyList[counter] = tmp;
			ch = strtok(NULL, ",");
//			printf("---------------->%d",*ch);
//			ch = strtok(NULL, "\t");
		}
			memset(line,0,1024);
	}
	printf("%s","Done reading file!!\n");	
			fflush(stdout);
	fclose(file);
}
	
void dijkstra()
{
	long int i=1;
	detail[1].shortestdistance =0;
	detail[1].viaNode = 1;
	int counter =1;
	long int node = 1;
	while(counter<= N)
	{
		detail[counter].visited = 1;
		long int smallestD = 100000;
		long int snode = 0;
		struct node *j = adjacencyList[i];
		while(j!=NULL)
		{
			if(j->cost + detail[counter].shortestdistance < smallestD)
			{
				smallestD = j->cost + detail[counter].shortestdistance;
				snode = j->nodeNum;
			}
			if(j->cost + detail[counter].shortestdistance < detail[j->nodeNum].shortestdistance)
			{
				detail[j->nodeNum].shortestdistance = j->cost + detail[counter].shortestdistance;
				detail[j->nodeNum].viaNode = counter;
			}
			j = j->next;
		}
//		detail[snode].shortestdistance = smallestD;
//		detail[snode].viaNode = i;
//		counter = snode;
		counter++;
	}	
}

void dij()
{
	long int i=2;
	struct Node tmp;
	tmp.d_fromsource = 0;
	tmp.pnodeIndex = 1;
	tmp.nodeIndex = 1;
	insert(tmp);
	while(i<=N)
	{
		tmp.d_fromsource = 1000000;
		tmp.pnodeIndex = 0;
		tmp.nodeIndex = i;
		insert(tmp);
		i++;
	}
	i=1;
	while(i<=N && currentSize <=N)
	{
		struct Node temp = removeMin();
//		printf("\nRemoved:%ld %ld\n", temp.nodeIndex,temp.d_fromsource);
		detail[temp.nodeIndex].shortestdistance = temp.d_fromsource;
		detail[temp.nodeIndex].viaNode = temp.pnodeIndex;
		struct node * j = adjacencyList[temp.nodeIndex];
		while(j!=NULL)
		{
			if(j->cost + detail[temp.nodeIndex].shortestdistance <= detail[j->nodeNum].shortestdistance)
			{
//				printf("Updated:%ld %ld %ld\n",j->nodeNum,j->cost + detail[temp.nodeIndex].shortestdistance,temp.nodeIndex);
				updateDistance(j->nodeNum, j->cost + detail[temp.nodeIndex].shortestdistance, temp.nodeIndex);
		/*		struct Node t;
				t.d_fromsource = j->cost + detail[temp.nodeIndex].shortestdistance;
				t.pnodeIndex = temp.nodeIndex;
				t.nodeIndex = j->nodeNum;
				insert(t); 
			*/	detail[j->nodeNum].shortestdistance = j->cost + detail[temp.nodeIndex].shortestdistance;
				detail[j->nodeNum].viaNode = temp.nodeIndex;
/*				int x = 1;
				long int smallest = firstelement().d_fromsource; 
					printf("Heap:\n");
				while(x <= currentSize)
				{
					if(heap[x].d_fromsource != 1000000)
					{
						printf("%d-%ld ",x,heap[x].d_fromsource);
					}
					else
					{
						printf("%d-__ ",x);

					}*/
	/*				if(smallest > heap[x].d_fromsource)
					{
						printf("Element smaller than first element[%ld] found %ld\n",smallest,heap[x].d_fromsource);
					}
*/
//					x++;
//				}
			}
			j = j->next;
		}
		i++;
	}
}

int main(int argc,char **argv)
{
	if (2!=argc)
	{
		printf("Syntax: <executable> <inputfile>\n");
		exit(1);
	}

	currentSize = 0;
	//read the input file and create adjacency list
	create_adjacency(argv[1]);
//	printAdjacency();
	int i=1;
	while(i<=N)
	{
		detail[i].shortestdistance = 1000000;
		i++;
	}
//	dijkstra();
	dij();
	i=1;
	while(i<=N)
	{
		if((i==7 || i==37 || i==59 || i==82 || i==99 || i==115 || i==133 || i==165 || i==188 || i==197) || all==1)
		{
			printf("%d\t%ld\t",i,detail[i].shortestdistance);
			printf("%ld",detail[i].viaNode);
		}
		long int j=detail[i].viaNode,c=0;
		while(j!= 1 && c<N)
		{
			if((i==7 || i==37 || i==59 || i==82 || i==99 || i==115 || i==133 || i==165 || i==188 || i==197) || all==1)
			{
				printf("-->%ld",detail[j].viaNode);
			}
			j = detail[j].viaNode;
			c++;
		}

		if((i==7 || i==37 || i==59 || i==82 || i==99 || i==115 || i==133 || i==165 || i==188 || i==197) || all==1)
		printf("\n");
		i++;
	}
	freegraph();
	return 1;
}
