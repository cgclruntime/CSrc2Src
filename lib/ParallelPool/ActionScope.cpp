#include "ParallelPool/ActionScope.h"
#include "ParallelPool/ParaFuncMgr.h"
#include "utl/OsUtils.h"
#include "ParallelPool/FuncContext.h"


ActionScope::ActionScope( ScopeID iSID )
	: mc_iScopeID(iSID)
	, m_bNeedDeconstruce(false)
{
	LOG_INFO("ActionScope","ActionScope()::enter scope : "<<mc_iScopeID);
}

ActionScope::~ActionScope(void)
{
	if(m_bNeedDeconstruce)
		exitScope();
}

void ActionScope::exitScope()
{
	m_bNeedDeconstruce = false;
	//To Fix it, waiting the parallel functions should be more smart!
	ParaFuncMgr & pMgr = ParaFuncMgr::getInstance();
	bool bNotComplete = true;
	LOG_INFO("ActionScope","exitScope(): exiting scope : "<<mc_iScopeID);

	while(bNotComplete)
	{
		if(m_vctPFs.empty())
		{
			bNotComplete = false;
			break;
		}
		bool bRes;
		for(int i = 0; i<m_vctPFs.size(); ++i)
		{
			if(i == 0)
				bRes = (m_vctPFs[i]->m_uiState == FuncContext::stat_over);
			else
				bRes = bRes && (m_vctPFs[i]->m_uiState == FuncContext::stat_over);
		}//如果有任何一个并行没有结束，则bRes为false
		bNotComplete = !bRes;
		if(bNotComplete)
			utl::sleep(1);
	}

	
	LOG_INFO("ActionScope","exitScope(): all function is over in "<<mc_iScopeID);
	ParaFuncSyn::getInstance().lock();
	LOG_INFO("ActionScope", "exitScope(), get lock");
	pMgr.clearScope(mc_iScopeID);
	ParaFuncSyn::getInstance().unlock();
}

void ActionScope::addPFunc( FuncContext *pContext )
{
	m_bNeedDeconstruce = true;
	m_vctPFs.push_back(pContext);
}


