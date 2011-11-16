#include "ParallelPool/WaitConds.h"


void AndWaitCond::setComplete( bool bIsComplete /*= true*/ )
{
	if(bIsComplete)
	{
		m_bIsComplete = true;
		if(m_pLChild)
			m_bIsComplete = m_bIsComplete && m_pLChild->isComplete();
		if(m_pRChild)
			m_bIsComplete = m_bIsComplete && m_pRChild->isComplete();

		if(m_bIsComplete)
			m_poParent->setComplete(true);
	}
}

void AndWaitCond::traverseConds( TraverseCallBack pCallBack )
{
	(*pCallBack)(this);
	if(m_pLChild)
		m_pLChild->traverseConds(pCallBack);
	if(m_pRChild)
		m_pRChild->traverseConds(pCallBack);
}

PFID AndWaitCond::getWaitPFID()
{
	PFID tmp;
	tmp.m_iPFID = 0;
	return tmp;
}

void OrWaitCond::setComplete( bool bIsComplete /*= true*/ )
{
	if(bIsComplete)
	{
		m_bIsComplete = false;
		if(m_pLChild)
			m_bIsComplete = m_bIsComplete || m_pLChild->isComplete();
		if(m_pRChild)
			m_bIsComplete = m_bIsComplete || m_pRChild->isComplete();
	}
}

void OrWaitCond::traverseConds( TraverseCallBack pCallBack )
{
	(*pCallBack)(this);
	if(m_pLChild)
		m_pLChild->traverseConds(pCallBack);
	if(m_pRChild)
		m_pRChild->traverseConds(pCallBack);
}

PFID OrWaitCond::getWaitPFID()
{
	PFID tmp;
	tmp.m_iPFID = 0;
	return tmp;
}

void LeafWaitCond::setComplete( bool bIsComplete /*= true*/ )
{
	m_bIsComplete = bIsComplete;
	if(m_bIsComplete)
		m_poParent->setComplete(true);
}

void LeafWaitCond::traverseConds( TraverseCallBack pCallBack )
{
	(*pCallBack)(this);
}

PFID LeafWaitCond::getWaitPFID()
{
	return m_iPFWait;
}

void AllWaitCond::setComplete( bool bIsComplete /*= true*/ )
{
	if(bIsComplete)
	{
		m_iCompleteNums++;
		if(m_iCompleteNums >= m_iPFWait.m_oDetails.m_iInst)
		{
			m_bIsComplete = true;
			m_poParent->setComplete(true);
		}
	}
}

void AllWaitCond::traverseConds( TraverseCallBack pCallBack )
{
	(*pCallBack)(this);
}

PFID AllWaitCond::getWaitPFID()
{
	return m_iPFWait;
}

void AnyWaitCond::setComplete( bool bIsComplete /*= true*/ )
{
	if(bIsComplete)
	{
		if(m_bIsComplete)
		{
			m_bIsComplete = true;
			m_poParent->setComplete(true);
		}
	}
}

void AnyWaitCond::traverseConds( TraverseCallBack pCallBack )
{
	(*pCallBack)(this);
}

PFID AnyWaitCond::getWaitPFID()
{
	return m_iPFWait;
}