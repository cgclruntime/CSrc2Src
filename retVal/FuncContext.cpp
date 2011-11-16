#include "FuncContext.h"

#include <cassert>
#include <stdlib.h>
#include <string.h>

FuncContext::FuncContext(void *pFuncAddr, const String & strPFName )
	: m_pFuncAddr(pFuncAddr)
	, m_strFuncName(strPFName)
	, m_iArgsLen(0)
{
	assert(pFuncAddr && "Null function addr!");
}

FuncContext::~FuncContext(void)
{
}

void FuncContext::runPFunc()
{
	assert(m_iArgsLen>0 && m_iArgsLen<MAX_ARGS_LEN && "Unexpected args len!");

	char tmp[MAX_ARGS_LEN << 1];

	get_stack_info(m_uiESP1, m_uiEBP1);

	memcpy((void *)m_uiESP1, m_acArgs, m_iArgsLen);

	__asm__ __volatile__(
		"call *%0"
		:
	: "m"(m_pFuncAddr)
		: "memory"
		);

	set_stack_info(m_uiESP1, m_uiEBP1);

}