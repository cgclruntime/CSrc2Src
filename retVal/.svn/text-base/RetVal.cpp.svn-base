#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define get_stack_info(esp,ebp)	\
	__asm__ __volatile__(		\
	"movl %%esp, %0\n\t"	\
	"movl %%ebp, %1"		\
	: "=m" (esp), "=m" (ebp)	\
	:		\
	: "memory"	\
	);

#define set_stack_info(esp,ebp) \
	__asm__ __volatile__(		\
	"movl %0, %%esp\n\t"		\
	"movl %1, %%ebp"			\
	:							\
	: "m"(esp), "m"(ebp)	\
	);


typedef unsigned char byte;

typedef struct big_thing
{
	char buf[30];
}big_thing;

unsigned int		m_uiESP1;
unsigned int		m_uiEBP1;

void *memcopy(void * destaddr, void * souraddr, int size)
{
   byte *destBaddr=(byte *)destaddr;
   byte *sourBaddr=(byte *)souraddr;
   printf("size is %d\n",size);
   while(size-->0)
       {
      *(destBaddr++)=*(sourBaddr++);
       }
}

char return_cRet()
{
get_stack_info(m_uiESP1, m_uiEBP1);
char c='a';
return c;
}

long long return_shortRet()
{
   get_stack_info(m_uiESP1, m_uiEBP1);
	long long t=64;
	return t;
}

big_thing return_test()
{
   get_stack_info(m_uiESP1, m_uiEBP1);
	big_thing b;
   for(int i =0;i<30;i++)
       {
      b.buf[i]=i;
       }
       
	return b;
}

int main()
{

	long long         s;
   void *            FuncAddr=(void *)return_shortRet;
	void *            RetAddr=&s;
	int               RetLen=sizeof(s);

	__asm__ __volatile__(
		"call *%0"
		:
	: "m"(FuncAddr)
		: "memory"
		);

	if(RetLen>0&&RetLen<5)
	{
		memcopy((void *)RetAddr, (void *)(m_uiEBP1-RetLen), RetLen);
	}
	else
	{
		memcopy((void *)RetAddr, (void *)(m_uiEBP1-RetLen), RetLen);
	}
	printf("long long: %lld\n",s);

char ct;
FuncAddr=(void *)return_cRet;
RetAddr=&ct;
RetLen=sizeof(ct);

	__asm__ __volatile__(
		"call *%0"
		:
	: "m"(FuncAddr)
		: "memory"
		);

	if(RetLen>0&&RetLen<9)
	{
		memcopy((void *)RetAddr, (void *)(m_uiEBP1-RetLen), RetLen);
	}
	else
	{
		memcopy((void *)RetAddr, (void *)(m_uiEBP1-RetLen), RetLen);
	}
	printf("char: %c\n",ct);

	big_thing           n;
   FuncAddr=(void *)return_test;
	RetAddr=&n;
	RetLen=sizeof(n);
   big_thing bt=return_test();
   big_thing btr=return_test();

	__asm__ __volatile__(
		"call *%0"
		:
	: "m"(FuncAddr)
		: "memory"
		);

	if(RetLen>0&&RetLen<5)
	{
		memcopy((void *)RetAddr, (void *)(m_uiEBP1-4), 4);
	}
	else if(RetLen>4&&RetLen<9)
	{
		memcopy((void *)RetAddr, (void *)(m_uiEBP1-8), 8);
	}
	else
	{
		memcopy((void *)RetAddr, (void *)(m_uiEBP1-RetLen), RetLen);
	}
	printf("second :");
	for(int i=0;i<30;i++)
	{
		printf(" %c", n.buf[i]);
	}
	return 0;
}
