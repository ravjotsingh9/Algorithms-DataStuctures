#include "header.h"

void readfile(char *inputfile,struct hashentry **ht)
{
	char line[80];
	FILE *file;
	file = fopen(inputfile,"r");
	printf("%s","Starting reading file ");	
	unsigned int counter = 0;
	while(fgets(line,80, file))
	{
	//	printf("\nline read:%s",line);
		if(counter%10000 == 0)
		{
			printf("*");	
			fflush(stdout);
		}
		char *ch;
		char v[20];
		strcpy(v,line);
//		printf("string:%s",v);
		ch = &(v[strlen(v)]);
		long long int val = strtoll(v,&ch,10);
//		printf("val:%lli\n",val);
		put(ht,val,M,N);
//		printf("val inserted\n");
		counter++;
		memset(line,0,80);
	}
	printf("Done Reading\n");
	fclose(file);
}

