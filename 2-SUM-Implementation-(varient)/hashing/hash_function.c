#include"hash_header.h"

void init(struct hashentry ***ptr_to_ht, long long int N)
{
	*ptr_to_ht = (struct hashentry **)malloc(sizeof(struct hashentry *) * (N));	
}

void put(struct hashentry ** ht, long long int val,long unsigned int m,long long int N )
{
	long long int key = generatekey(val,m,N);
//	printf("key:%lli",key);
	if(key >= N)
	{
		printf("\n***Error*** key is > N. key:%lli N:%lli\n",key,N);
		exit(0);
	}
	if(getandRemove(ht,val,m,N,0)==-1)
	{
		insertInList(ht,key,val);
	}
}

long long int  generatekey(long long int val, long unsigned int m, long long int N)
{
	if(val < 0)
	{
		val = 0 - val; 
	}
	return (val%N);
}

void insertInList(struct hashentry ** ht, long unsigned int key,long long int val)
{
	struct hashentry *tmp = (struct hashentry *)malloc(sizeof(struct hashentry));
	tmp->val = val;
	tmp->next = ht[key];
	ht[key] = tmp;
}

int getandRemove(struct hashentry ** ht,long long int val,long unsigned int m, long long int N, int remove)
{
	long long int key = generatekey(val,m,N);
	if(key >= N)
	{
		printf("\n***Error*** key is > N. key:%lli N:%lli\n",key,N);
		exit(0);
	}
	return ifexist(ht,key,val,remove);	
}

int ifexist(struct hashentry ** ht, long unsigned int key, long long int val, int remove)
{
	struct hashentry * prev, *ptr = ht[key];
	prev = ht[key];
	while(ptr != NULL)
	{
		if(ptr->val == val)
		{
			if(remove)
			{
				if(prev!= ht[key])
				{
					if(ptr->next!=NULL)
					{
						prev->next = ptr->next;
						free(ptr);
						ptr = NULL;
					}
					else
					{
						prev->next = NULL;
						free(ptr);
						ptr = NULL;
					}
				}
				else
				{
					if(ptr->next!=NULL)
					{
						ht[key] = ptr->next;
						free(ptr);
						ptr = NULL;
					}
					else
					{
						ht[key] = NULL;
						free(ptr);
						ptr = NULL;
					}
				}
			}
			return 0;
		}
		prev = ptr; 
		ptr = ptr->next;
	}
	return -1;
}

void freeht(struct hashentry *** ptr_to_ht, long long int N )
{
	long long int i =0;
	while(i<N)
	{
		if((*ptr_to_ht)[i]!=NULL)
		{
			freelist((*ptr_to_ht)[i]);
		}
		i++;
	}
}

void freelist(struct hashentry *ptr)
{
	if(ptr->next == NULL)
	{
		free(ptr);
		ptr= NULL;
		return;		
	}
	else
	{
		freelist(ptr->next);
		free(ptr);
		ptr= NULL;
		return;		
	}
}

void print(struct hashentry **ht,long long int N)
{
	long long int i = 0;
	while(i<N)
	{
		printf("\n %lli> ",i);
		struct hashentry * ptr = ht[i];
		while(ptr!=NULL)
		{
			printf("%lli\t",ptr->val);
			ptr = ptr->next;
		}
		i++;
	}
	printf("\n");
}
