#include "ParaHeader.h"
#include <cassert>

ParaFuncSyn ParaFuncSyn::sv_oInstance;

#include "utl/UtlImpl.cxx"

void parallelFunc(FuncContext *pContext, int iPoolSize)
{
	static ParaFuncMgr & PFMgr = ParaFuncMgr::getInstance();
	static ParaPool PFPool(iPoolSize, PFMgr);

	if(!pContext)
		return ;

	LOG_INFO("parallelFunc","enter the parallel process: "<<pContext->m_strFuncName);
	ParaFuncSyn::getInstance().lock();

	if(pContext->m_uiState == FuncContext::stat_init)
	{
		PFMgr.getOrInsertPF(pContext);
	}
	else
	{
		//不应该重复使用同一个pContext
		ParaFuncSyn::getInstance().unlock();
		assert(0 && "Cannot use the same FuncContext more than one time!");
	}
	
	ParaFuncSyn::getInstance().unlock();

	pContext->m_oScope.addPFunc(pContext);

	if(pContext->m_poWaitConditions)
		PFPool.scheduleWaitPFunc(pContext);
	else
		PFPool.schedulePFunc(pContext);
}
