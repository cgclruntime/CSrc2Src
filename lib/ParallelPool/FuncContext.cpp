#include "ParallelPool/FuncContext.h"

#include <cassert>
#include <stdlib.h>
#include <string.h>


FuncContext::FuncContext( ActionScope & oScope, void *pFuncAddr, const String & strPFName )
	: m_oScope(oScope)
	, m_pFuncAddr(pFuncAddr)
	, m_strFuncName(strPFName)
	, m_poWaitConditions(NULL)
	, m_iArgsLen(0)
	, m_uiState(FuncContext::stat_init)
{
	assert(pFuncAddr && "Null function addr!");
	//m_oScope.addPFunc()
	LOG_INFO("FuncContext", "FuncContext(),construct FuncContext: "<<strPFName);
}

FuncContext::~FuncContext(void)
{
	LOG_INFO("FuncContext", "~FuncContext(), deconstruct FuncContext: "<<m_strFuncName);
}

void FuncContext::addWaitCond( WaitCondBase * pWaitConds )
{
	m_poWaitConditions = pWaitConds;
}

void FuncContext::runPFunc()
{
	assert(m_iArgsLen>0 && m_iArgsLen<MAX_ARGS_LEN && "Unexpected args len!");

	char tmp[MAX_ARGS_LEN << 1];//used to make sure the stack size!
	
	get_stack_info(m_uiESP1, m_uiEBP1);

	memcpy((void *)m_uiESP1, m_acArgs, m_iArgsLen);

	__asm__ __volatile__(		//µ÷ÓÃº¯Êý
		"call *%0"
		:
	: "m"(m_pFuncAddr)
		: "memory"
		);
	set_stack_info(m_uiESP1, m_uiEBP1);
	LOG_INFO("FuncContext","runPFunc(): running func: ");
}


