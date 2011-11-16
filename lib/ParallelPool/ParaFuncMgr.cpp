#include "ParallelPool/ParaFuncMgr.h"
#include "ParallelPool/WaitConds.h"
#include "ParallelPool/FuncContext.h"

#include <cassert>

ParaFuncMgr * ParaFuncMgr::sv_pInstance = new ParaFuncMgr();



void ParaFuncMgr::traverseSetWaitsCond(WaitCondBase *pWaitCond)
{
	static PFWaitsContainer & PFWaits = sv_pInstance->m_mapPFWaits;
	PFID oTmpPF;
	if(pWaitCond->isLeafWaitCond())
	{
		oTmpPF = pWaitCond->getWaitPFID();
		PFWaitsContainer::iterator Wait_it = PFWaits.find(oTmpPF);
		if(Wait_it == PFWaits.end())
			assert(0 && "Cannot find the waitee function!");
		Wait_it->second->push_back(pWaitCond);
	}
}

ParaFuncMgr::ParaFuncMgr(void)
{
}


ParaFuncMgr::~ParaFuncMgr(void)
{
}

ParaFuncMgr & ParaFuncMgr::getInstance()
{
	return *sv_pInstance;
}

ParaFuncMgr::ParaFuncInfo * ParaFuncMgr::getOrInsertPF( FuncContext *pCtxt )
{
	PFID oTmpPF = pCtxt->m_iFuncID;
	ParaFuncInfo * pInfo = NULL;
	//1.生成编号,若有多个实例的话，该编号一样，多个实例只需保存第一个信息
	oTmpPF = m_oPFIDGenerator.generatePFID(pCtxt);
	LOG_INFO("ParaFuncMgr","getOrInsertPF(), enter" << pCtxt->m_strFuncName);
	ParaFuncContainer::iterator PF_it = m_mapAllPFs.find(oTmpPF);
	if(PF_it == m_mapAllPFs.end())//没有找到，则需要插入
	{
		LOG_INFO("ParaFuncMgr","getOrInsertPF(): insert para func: "<<pCtxt->m_strFuncName);

		pCtxt->m_iFuncID = oTmpPF;
		pCtxt->m_iFuncID.m_oDetails.m_iInst ++;

		//2.创建FuncInfo
		pInfo = new ParaFuncInfo();
		assert(pInfo && "Alloc error!");
		pInfo->m_iParaFuncID = pCtxt->m_iFuncID;
		pInfo->m_poContext = pCtxt;
		pInfo->m_poWaitConds = pCtxt->m_poWaitConditions;
		if(pInfo->m_poWaitConds)
			pInfo->m_uiState = FuncContext::stat_wait;
		else
			pInfo->m_uiState = FuncContext::stat_ready;

		//3.插入到m_mapAllPFs
		m_mapAllPFs.insert(std::make_pair(oTmpPF, pInfo));

		//4.创建WaitsContainer
		WaitsContainer *pWaits = new WaitsContainer();
		assert(pWaits && "Alloc error!");

		//5.插入m_mapPFWaits
		m_mapPFWaits.insert(std::make_pair(oTmpPF, pWaits));

		//6.设置相应的等待条件
		if(pInfo->m_poWaitConds)
			pInfo->m_poWaitConds->traverseConds(ParaFuncMgr::traverseSetWaitsCond);

		return pInfo;
	}
	else								//查找成功
	{
		pInfo = PF_it->second;
		assert(pInfo && "Null PF information!");
		LOG_INFO("ParaFuncMgr", "getOrInsert(), find failed!");
		
		//多个实例，则保存必要的信息
		pInfo->m_iParaFuncID.m_oDetails.m_iInst ++;
		pInfo->m_poContext->m_iFuncID.m_oDetails.m_iInst ++;

		if(pCtxt->m_poWaitConditions)
			pCtxt->m_poWaitConditions->traverseConds(ParaFuncMgr::traverseSetWaitsCond);

		return pInfo;
	}
}

ParaFuncMgr::ParaFuncInfo * ParaFuncMgr::getPF( const PFID &iPF )
{
	ParaFuncContainer::iterator PF_it = m_mapAllPFs.find(iPF);
	if(m_mapAllPFs.end() == PF_it)
	{
		LOG_INFO("ParaFuncMgr","getPF(), cannot find this function in mgr" << iPF.m_oDetails.m_iScope<<" "<<iPF.m_oDetails.m_iFunc);
		return NULL;
	}
	assert(PF_it->second);
	return PF_it->second;
}

ParaFuncMgr::WaitsContainer * ParaFuncMgr::getPFWaits( const PFID &iPF )
{
	PFWaitsContainer::iterator it = m_mapPFWaits.find(iPF);
	if(it == m_mapPFWaits.end())
	{
		LOG_INFO("ParaFuncMgr","getPF(), cannot find this function in mgr" << iPF.m_oDetails.m_iScope<<" "<<iPF.m_oDetails.m_iFunc);
		return NULL;
	}
	assert(it->second);
	return it->second;
}

void ParaFuncMgr::clearScope(U16 iScopeID)
{
	//ParaFuncSyn::getInstance().lock(); has been called by ActionScope.exitScope();
	LOG_INFO("ParaFuncMgr", "clearScope(), scope id: "<<iScopeID);
	m_oPFIDGenerator.clearScopeData(iScopeID);
	
	//release memory!
	ParaFuncContainer::iterator it;
	for(it = m_mapAllPFs.begin(); it!=m_mapAllPFs.end(); ++it)
	{
		if(m_mapAllPFs.end() == it)
		{
			return ;
		}
		if(it->first.m_oDetails.m_iScope == iScopeID)
		{
			ParaFuncInfo *pInfo = it->second;
			assert(pInfo && "Unknown null pointer!");

			assert(pInfo->m_poContext && "pContext is null in ParaFuncInfo!");
			delete pInfo->m_poContext;

			if(pInfo->m_poWaitConds)
				delete pInfo->m_poWaitConds;

			delete it->second;

			m_mapAllPFs.erase(it);
			it = m_mapAllPFs.begin();
		}
	}
	//ParaFuncSyn::getInstance().unlock(); called by ActionScope.exitScope();
}


