#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAX = 1 << 20;
int data[MAX], l;
int S[MAX];

void sum(int , int, int*);
void getData();

void getData()
{
	l = MAX; 
	srand(time(NULL));
	for(int i = 0; i < l; i++)
		data[i] = rand() & 1023;
}

void sum(int begin, int end, int *s)
{
	*s = 0;
	for(int i = begin; i < end; i++) *s += data[i];
}

int main()
{
	memset(S, 0, sizeof(S));
	
	getData();
	parallel sum s;
	for(int i = 0; i < l / 4; i++)
		s(i << 2, (i << 2) | 1, &S[i]);
		
	int rt = 0;
	for(int i = 0; i < l / 4; i++)
		rt += S[i];
	for(int i = 0; i < l; i++) rt -= data[i];
	if(i == 0) printf("OK\n");
	else printf("Error\n");
	
	return 0;
}