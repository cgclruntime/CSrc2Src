#include <stdio.h>
#include "Types.h"
#include "FuncContext.h"

//typedef struct lr
//{
//	int addr[256];
//}longRet;

int return_shortRet()
{
	int shortRet=12;
	return shortRet;
}

void _fake_processreturnSRet_2(FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP2, pCtxt->m_uiEBP2);
	pCtxt->m_iArgsLen = pCtxt->m_uiEBP1->pCtxt->m_uiEBP2-8;
	memcpy(pCtxt->m_acArgs, (void *)(pCtxt->m_uiEBP2+8), pCtxt->m_iArgsLen);
}

void _fake_processreturnSRet_1(FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP1, pCtxt->m_uiEBP1);
	_fake_processreturnSRet_2(pCtxt);
}

//longRet return_longRet()
//{
//	longRet lr={12,34,56};
//	return lr;
//}

int main()
{
	int va1;

	FuncContext *pCtxt = new FuncContext((void *)return_shortRet, "return_shortRet");
	_fake_processreturnSRet_1(pCtxt);
	pCtxt.runFunc();
	va1=return_shortRet();

	printf("return shortRet: %d\n", va1);

	return 0;
}