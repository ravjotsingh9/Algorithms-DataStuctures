#include "header.h"

int main(int argc, char **argv)
{
	if (2!=argc)
	{
		printf("Syntax: <executable> <inputfile>\n");
		exit(1);
	}

	N = 1000003;
	M = 1000;
	init(&ht,N);	
	readfile(argv[1],ht);
//	print(ht,N);

	int flag=0;
	long long int counter = 0,t =-10000,x = 0, y= 0,pass =0;
	while(t<=10000)
	{
		printf("%lli ",t);
		fflush(stdout);
		flag=0;
		pass = 0;
		while(pass < N)
		{
			struct hashentry * tmp = ht[pass];
			while(tmp !=NULL)
			{
				x = tmp->val;
				y = t-x;
				if(x==y)
				{
					break;
				}
				if(getandRemove(ht,y,M,N,0)==0)
				{
					counter++;
					flag =1;
					break;
				}
				tmp = tmp->next;
			}
			if(flag == 1)
			{
				break;
			}
			pass++;
		}
		t++;
	}
	printf("Counter:%llu\n",counter);
	freeht(&ht,N);
}
