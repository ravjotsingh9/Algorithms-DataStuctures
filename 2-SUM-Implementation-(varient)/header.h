#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./hashing/hash_header.h"
long long int N;
long long int M;
struct hashentry ** ht;
void readfile(char *inputfile, struct hashentry **ht);
