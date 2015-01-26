#include<stdio.h>
#include<stdlib.h>

struct hashentry
{
	long long int val;
	struct hashentry * next;
};

void init(struct hashentry *** ht, long long int N);
void put(struct hashentry ** ht, long long int val,long unsigned int m, long long int N );
long long int  generatekey(long long int val, long unsigned int m,long long int N);
void insertInList(struct hashentry **ht, long unsigned int key,long long int val);
int getandRemove(struct hashentry **ht,long long int val,long unsigned int m, long long int N,int remove);
int ifexist(struct hashentry **ht, long unsigned int key, long long int val, int remove);
void freeht(struct hashentry *** ht, long long int N );
void freelist(struct hashentry *ptr);
void print(struct hashentry **ht, long long int N );
