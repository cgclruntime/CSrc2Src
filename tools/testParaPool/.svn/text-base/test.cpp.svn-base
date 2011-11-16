#include <stdio.h>
#include "ParaHeader.h"

int data[1 << 25], seq[1 << 25];
int sum = 0;

void init()
{
	srand(time(NULL));
	for(int i = 0; i < 1 << 25; i++) data[i] = seq[i] = rand() & ((1 <<25) - 1);
	printf("over\n");
}

void func(int a, int b);

void _fake_func_1(int a, int b, FuncContext *pCtxt);
void _fake_func_2(int a, int b, FuncContext *pCtxt);


void func(int a,int b)
{
	for(int j = 0; j < 3; j++)
	for(int i = a; i < b; i++) sum += data[seq[i]];
}

/*
void func(int a, int b)
{
	for(int i = a; i < b; i++) sum += data[seq[i]];
}
*/
void _fake_func_1(int a, int b, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP1, pCtxt->m_uiEBP1);
	_fake_func_2(a,b, pCtxt);
}
void _fake_func_2(int a, int b, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP2, pCtxt->m_uiEBP2);
	pCtxt->m_iArgsLen = pCtxt->m_uiEBP1-pCtxt->m_uiEBP2-8;
	memcpy(pCtxt->m_acArgs, (void *)(pCtxt->m_uiEBP2+8), pCtxt->m_iArgsLen);
}
int main(int argc, char *argv[])
{
	init();
	utl::startLogInfrastrue("log.txt",40000);
	
	clock_t start = clock();
	ActionScope s_main(1);
	
	FuncContext *pCtxt = new FuncContext(s_main, (void *)func, "f1");	
	_fake_func_1(0, 1 << 24, pCtxt);
	//FuncContext *pCtxt1 = new FuncContext(s_main, (void *)func, "f2");
	//_fake_func_1(1 <<24, 1 <<25, pCtxt1);

	parallelFunc(pCtxt);
	//parallelFunc(pCtxt1);
	
	s_main.exitScope();
	
	printf("%.5lf\n", (clock() - start) / (double)CLOCKS_PER_SEC);
	printf("%d\n", sum);
	return 0;
}
