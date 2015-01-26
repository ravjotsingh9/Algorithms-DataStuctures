#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define FAILURE 0
#define SUCCESS 1
#define IN
#define OUT
#define MOD
/* total number of vertices */
#define N  875714
//#define N  9

/* struct ot hold arcs */
struct Arc
{
	unsigned int connectedto;
	struct Arc * nextarc;
};
/* list of vertices */
struct Arc * vertex[N+1]={0};
struct Results
{
	unsigned int leader;
	int explored;
};
unsigned int nodeWithiftime[N+1]={0};
unsigned int chelecount[N+1]={0};
unsigned int stack[N+1]={0};
unsigned int top = 0;
/* to print current timestamp */
struct tm printcurrentts()
{
	time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
	printf ( "<<TimeStamp>>:%s", asctime (timeinfo) );
	return *timeinfo;
}
/* to print entire adjacency matrix: might take a long time*/
void printAdjacency()
{
	int i=1;
	printf("%s\n","Printing:");	
	while(i<= N)
	{
		if(i%10000==0)
		{
				printf("*");
			fflush(stdout);	
		}
		printf("%d\t", i);
		if(vertex[i]!= NULL)
		{
			struct Arc * j =vertex[i];
			while(j != NULL)
			{
				printf("%d\t", j->connectedto);
				int x = j->connectedto;
				if(x<=0 || x> N)
				{
					printf("Vertex:%d x:%d \n",i,x);
					fflush(stdout);	
				}
				j = j->nextarc;
			}
		}
		printf("\n");
		i++;
	}
	printf("%s\n","Printed!!");	
}

/* free memory: used while free-ing graph memory */
void memfree(struct Arc * ptr)
{
	if(ptr!=NULL)
	{
		ptr = ptr->nextarc;
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
	printcurrentts();
	printf("%s\n","Starting free-ing the memory:");	
	int i=1;
	while(i<=N)
	{
		if(i%10000 == 0)
		{
			printf("#");
			fflush(stdout);	
		}
		if(vertex[i]!= NULL)
		{
			memfree(vertex[i]);
		}
		vertex[i]=NULL;
		i++;
	}
	printf("%s\n","Free-ed!!");	
}

unsigned int t = 0;
void dfsloop(int rev)
{
	struct Results result[N+1]= {0};
	if(1== rev)
	{
		unsigned int i = N;
		while(i >0)
		{
			if(0==result[i].explored)
			{
				dfs_nonR(i,i,result,rev);
			}
			i--;
		}
/*		printf("%s\n","Found leaders:");	
	 	i=1;
		unsigned int prev =0;
		printf("\nVertexNumber\tLeader\tExplored\n");
		while(i<=N)
		{
			printf("%d\t",i);
			printf("\t%d",result[i].leader);
			printf("\t%d\n",result[i].explored);
			prev = i;
			i++;
		}
*/
	}
	else
	{
		unsigned int i = N;
		while(i > 0)
		{
			if(0 == result[nodeWithiftime[i]].explored)
			dfs_nonR(nodeWithiftime[i],nodeWithiftime[i],result, rev);
			i--;
		}
		printf("%s\n","Found leaders:");	
		unsigned int l1 =0;
		unsigned int l2 =0;
		unsigned int l3 =0;
		unsigned int l4 =0;
		unsigned int l5 =0;
		i=1;
		while(i<=N)
		{
			chelecount[result[i].leader]++;
			if(chelecount[result[i].leader] > l1)
			{
				l5 = l4;
				l4 = l3;
				l3 = l2;
				l2 = l1;
				l1 = chelecount[result[i].leader];
			}
			else
			{
				if(chelecount[result[i].leader] > l2)
				{
					l5 = l4;
					l4 = l3;
					l3 = l2;
					l2 = chelecount[result[i].leader];
				}
				else
				{
					if(chelecount[result[i].leader] > l3)
					{
						l5 = l4;
						l4 = l3;
						l3 = chelecount[result[i].leader];
					}
					else
					{			
						if(chelecount[result[i].leader] > l4)
						{
							l5 = l4;
							l4 = chelecount[result[i].leader];
						}
						else
						{
							if(chelecount[result[i].leader] > l5)
							{
								l5 = chelecount[result[i].leader];
							}
						}
					}
				}
			}	
			i++;
		}
		printf("1 >>> %u\n",l1);
		printf("2 >>> %u\n",l2);
		printf("3 >>> %u\n",l3);
		printf("4 >>> %u\n",l4);
		printf("5 >>> %u\n",l5);
			printf("Chelecount:\n");
		for(i=1;i<=N;i++)
		{
			printf("%u,",chelecount[i]);
		}
			printf("Chelecount Done!!\n");
	 	i=1;
		for(i=1;i<=6;i++)
		{
			int j=1;
			for(j=2;j<=N;j++)
			{
				if(chelecount[j-1]>chelecount[j])
				{
					unsigned int tmp = chelecount[j-1];
					chelecount[j-1] = chelecount[j];
					chelecount[j] = tmp;
				}
			}
		}
		printf("LEADERS:\n");
		printf("1 >>> %u\n",chelecount[N]);
		printf("2 >>> %u\n",chelecount[N-1]);
		printf("3 >>> %u\n",chelecount[N-2]);
		printf("4 >>> %u\n",chelecount[N-3]);
		printf("5 >>> %u\n",chelecount[N-4]);
		printcurrentts();
	}
}

void dfs_nonR(unsigned int vertexindex,unsigned int leadervertexindex,struct Results * result,int rev)
{
	int flag=0;
	result[vertexindex].explored = 1;
	result[vertexindex].leader = leadervertexindex;
	top++;
	stack[top]= vertexindex;
	while(top!=0)
	{
		unsigned int v = stack[top];
//		stack[top]=0; top--;
		struct Arc * j = vertex[v];
		flag=0;
		while(j!=NULL)
		{
			if(1 != result[j->connectedto].explored)
			{
				flag=1;
				result[j->connectedto].explored = 1;
				result[j->connectedto].leader = leadervertexindex;
				top++;
				stack[top]= j->connectedto;	
			}
			j = j->nextarc;
		}
		if(1==rev && flag==0)
		{
			t++;
			nodeWithiftime[t] = v;
		}
		if(0==flag)
		{
			stack[top]=0; top--;
		}
	}	
}

void dfs(unsigned int vertexindex,unsigned int leadervertexindex,struct Results * result,int rev)
{
//	printf("Entered dfs: vertex index= %d leadervertexindex= %d t=%d\n", vertexindex,leadervertexindex,t);
//			fflush(stdout);
	result[vertexindex].explored = 1;
//	printf("1\n");
//			fflush(stdout);
	result[vertexindex].leader = leadervertexindex;
//	printf("2\n");
//			fflush(stdout);
	struct Arc * j = vertex[vertexindex];
//	printf("3\n");
//			fflush(stdout);
	while(j!= NULL)
	{
		if(j->connectedto != 0)
		{	
	//		printf("result[j->connectedto].explored : %d \n",result[j->connectedto].explored);
//			fflush(stdout);
			if(1 != result[j->connectedto].explored)
			{
//				printf("4\n");
//			fflush(stdout);
				if(result!= NULL || j!=NULL || (leadervertexindex >0 && leadervertexindex <=N))
				{
//					printf("GOing to call dfs: j->connectedto= %d leadervertexindex= %d setleader=%d\n", j->connectedto,leadervertexindex,result[j->connectedto].leader);
//					fflush(stdout);
					dfs(j->connectedto,leadervertexindex, result,rev);
				}
				else
				{
					printf("*****************************Error******************* result found NULL\n");
					exit(1);
				}
//				printf("5\n");
//			fflush(stdout);
			}
		}
//	printf("6\n");
//			fflush(stdout);
		j = j->nextarc;
//	printf("7\n");
//			fflush(stdout);
	}
	if(1==rev)
	{
//	printf("8\n");
//			fflush(stdout);
		t++;
		nodeWithiftime[t] = vertexindex;
//	printf("9\n");
//			fflush(stdout);
	}
}

void createRevGraph(char * inputfile)
{
	char line[80];
	FILE *file;
	file = fopen(inputfile,"r");
	printf("%s","Starting reading file ");	
	unsigned int counter = 0;
	while(fgets(line,80, file))
	{
		if(counter%100000 == 0)
		{
			printf("*");	
			fflush(stdout);
		}
		char *ch;
		char f[20], t[20];
		unsigned int from = 1;
		unsigned int to = 1;
		ch = strtok(line," ");
		strcpy(t,ch);
		ch = strtok(NULL, "\n");
		strcpy(f,ch);
		from = atol(f);
		to = atol(t);
		if(from > N || to > N)
		{
			printf("Values Greater than N found: from %d, to %d\n",from,to);
			fflush(stdout);
		}
		if(from <= 0 || to <= 0)
		{
			printf("Values Smaller than 0 found: from %d, to %d\n",from,to);
			fflush(stdout);
		}
		struct Arc * tmp = (struct Arc *) malloc(sizeof(struct Arc));
		tmp->connectedto = to;
		tmp->nextarc = vertex[from];
		vertex[from] = tmp;
		counter++;
	}
	fclose(file);
}

void createGraph(char * inputfile)
{
	char line[80];
	FILE *file;
	file = fopen(inputfile,"r");
	printf("%s","Starting reading file ");	
	unsigned int counter = 0;
	while(fgets(line,80, file))
	{
		if(counter%100000 == 0)
		{
			printf("*");	
			fflush(stdout);
		}
		char *ch;
		char f[20], t[20];
		unsigned int from = 1;
		unsigned int to = 1;
		ch = strtok(line," ");
		strcpy(f,ch);
		ch = strtok(NULL, "\n");
		strcpy(t,ch);
		from = atol(f);
		to = atol(t);
		struct Arc * tmp = (struct Arc *) malloc(sizeof(struct Arc));
		tmp->connectedto = to;
		tmp->nextarc = vertex[from];
		vertex[from] = tmp;
		counter++;
	}
	fclose(file);
}

/* MAIN FUNCTION */
int main(int argc, char **argv)
{
	if(2!=argc)
	{
		printf("./a.out <inputfile>\n");
		return FAILURE;
	}
	printf("\n#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*# Execution Started #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n");
	printf("%s\n","Start creating rev graph at");	
	printcurrentts();
	createRevGraph(argv[1]);
	printf("%s\n","Done creating rev graph at");	
	printcurrentts();
	//printAdjacency();
	printf("%s\n","Start dfsloop rev graph at");	
	dfsloop(1);
	printf("%s\n","Done dfsloop rev graph at");	
	printcurrentts();
/*				int j=1;
				while(j<=N)
				{
					printf("%d\n",nodeWithiftime[j]);
					j++;
				}*/
	printf("%s\n","Start free-ing rev graph");	
	freegraph();
	printf("%s\n","Done free-ing rev graph at");	
	printcurrentts();
	printf("%s\n","Start creating graph at");	
	printcurrentts();
	createGraph(argv[1]);
	printf("%s\n","Done creating graph at");	
//	printAdjacency();
	printcurrentts();
	printf("%s\n","Start dfsloop graph at");	
	dfsloop(0);
	printf("%s\n","Done dfsloop graph at");	
	printcurrentts();
/*				j=1;
				while(j<=N)
				{
					printf("%d\n",nodeWithiftime[j]);
					j++;
				}*/
	printf("%s\n","Start free-ing graph");	
	freegraph();
	printf("%s\n","Done free-ing graph at");	
	printcurrentts();
	printf("#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*# Execution Completed #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n");
	return SUCCESS;
}

