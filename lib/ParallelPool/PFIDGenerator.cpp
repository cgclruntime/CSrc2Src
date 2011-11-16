#include "ParallelPool/PFIDGenerator.h"
#include "ParallelPool/FuncContext.h"
#include <cassert>

PFIDGenerator::PFIDGenerator(void)
{
}


PFIDGenerator::~PFIDGenerator(void)
{
}

PFID PFIDGenerator::generatePFID( FuncContext * pCtxt )
{
	PFID tmp;
	tmp.m_oDetails.m_iScope = pCtxt->getScopeID();

	//1.查找是否有此作用域
	ScopeAndFuncs *pFuncs = NULL;
	ScopeContainer::iterator itScope = m_oPFIDs.find(tmp.m_oDetails.m_iScope);
	if(itScope == m_oPFIDs.end())
	{
		pFuncs = new ScopeAndFuncs();
		assert(pFuncs && "Alloc error!");
		pFuncs->m_iScopeID = tmp.m_oDetails.m_iScope;
		m_oPFIDs.insert(std::make_pair(pFuncs->m_iScopeID, pFuncs));
	}
	else
	{
		pFuncs = itScope->second;
	}

	if(pFuncs->m_pFuncs == NULL)
	{
		pFuncs->m_pFuncs = new FuncContainer();
		assert(pFuncs->m_pFuncs && "Alloc error!");
	}
	
	//2.查找作用域下是否有此函数
	FuncContainer *pFunc = pFuncs->m_pFuncs;
	FuncAndParas *pParas = NULL;
	FuncContainer::iterator itFunc = pFunc->find(pCtxt->m_pFuncAddr);
	if(itFunc == pFunc->end())
	{
		pParas = new FuncAndParas();
		assert(pParas && "Alloc error!");
		pParas->m_iFuncID = pFunc->size() + 1;
		tmp.m_oDetails.m_iFunc = pParas->m_iFuncID;
		pParas->m_pParas = new Para2IDContainer();
		assert(pParas->m_pParas && "Alloc error!");
		pFunc->insert(std::make_pair(pCtxt->m_pFuncAddr, pParas));
	}
	else
	{
		pParas = itFunc->second;
		assert(pParas && "Null pointer!");
	}

	//3.查找此函数下是否有此并行函数
	Para2IDContainer *pPara = pParas->m_pParas;
	assert(pPara && "Null pointer!");
	Para2IDContainer::iterator itPara = pPara->find(pCtxt->m_strFuncName);
	if(itPara == pPara->end())
	{
		tmp.m_oDetails.m_iPara = pPara->size()+1;
		pPara->insert(std::make_pair(pCtxt->m_strFuncName,tmp.m_oDetails.m_iPara));
	}
	else
	{
		tmp.m_oDetails.m_iPara = itPara->second;
	}

	tmp.m_oDetails.m_iInst = 0;
	//pCtxt->m_iFuncID.m_iPFID = tmp.m_iPFID;
	return tmp;
}

void PFIDGenerator::clearScopeData( U16 iScopeID )
{
	LOG_INFO("PFIDGenerator", "clearScopeData(), scope id: "<<iScopeID);
	//1.查找是否有此作用域
	ScopeAndFuncs *pFuncs = NULL;
	ScopeContainer::iterator itScope = m_oPFIDs.find(iScopeID);
	if(itScope == m_oPFIDs.end())
	{
		return ;
	}
	else
	{
		pFuncs = itScope->second;
		assert(pFuncs && "Null pointer!");
	}

	FuncContainer *pFunc = pFuncs->m_pFuncs;
	FuncContainer::iterator itFunc;
	for(itFunc = pFunc->begin(); itFunc!=pFunc->end(); ++itFunc)
	{
		delete itFunc->second->m_pParas;
		delete itFunc->second;
	}
	delete pFuncs;
	m_oPFIDs.erase(itScope);
}
