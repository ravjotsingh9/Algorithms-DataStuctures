#include "hash_header.h"
#define N 17
#define M 10
void main()
{
 	struct hashentry ** ht;
	init(&ht,N);
	put(ht, 703, M,N);	
	put(ht, 700, M,N);	
	put(ht, 701, M,N);	
	put(ht, 800, M,N);	
	put(ht, 802, M,N);	
	getandRemove(ht,802,M,N,0);
	long unsigned int i = 1;
	while(i<=N)
	{
		printf("\n> ");
		struct hashentry * ptr = ht[i];
		while(ptr!=NULL)
		{
			printf("%lli\t",ptr->val);
			ptr = ptr->next;
		}
		i++;
	}
	printf("\n");
	freeht(&ht,N);
}
