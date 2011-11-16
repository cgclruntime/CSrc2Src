#ifndef _PARALLEL_POOL_WAIT_CONDS_H
#define _PARALLEL_POOL_WAIT_CONDS_H

#include "ParallelPool/Types.h"
#include "utl/Threads.h"
#include "utl/Log.h"


class WaitCondBase
{
protected:
	WaitCondBase(WaitCondBase *pParent)
		: m_poParent(pParent)
		, m_bIsComplete(false){};
public:
	virtual ~WaitCondBase(){};

	virtual void						setParent(WaitCondBase *pParent){m_poParent = pParent;};

	//************************************
	// Method:    isComplete
	// FullName:  WaitCondBase::isComplete
	// Access:    virtual public 
	// Returns:   bool
	// Qualifier: 判定该节点的值m_bIsComplete；
	//************************************
	virtual bool						isComplete() = 0;

	//************************************
	// Method:    setComplete
	// FullName:  WaitCondBase::setComplete
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: 修改该节点的值，若该节点的值为true，则修改其父节点的值
	// Parameter: bool bIsComplete
	//************************************
	virtual void						setComplete(bool bIsComplete) = 0;

	virtual	void						traverseConds(TraverseCallBack pCallBack) = 0;

	virtual PFID						getWaitPFID() = 0;

	virtual bool						isLeafWaitCond() = 0;
	virtual bool						isRootWaitCond() = 0;

protected: 
	WaitCondBase *						m_poParent;			//父亲节点指针，根节点的父亲节点指针为NULL
	bool								m_bIsComplete;
};


class AndWaitCond : public WaitCondBase{
public:
	AndWaitCond(WaitCondBase *pLChild, WaitCondBase *pRChild)
		: WaitCondBase(NULL)
		, m_pLChild(pLChild)
		, m_pRChild(pRChild)
	{
		if(m_pLChild)
			m_pLChild->setParent(this);
		if(m_pRChild)
			m_pRChild->setParent(this);
	};
	virtual ~AndWaitCond(){
		if(m_pLChild)
			delete m_pLChild;
		if(m_pRChild)
			delete m_pRChild;
	};

	virtual bool						isComplete()
	{
		if(m_bIsComplete)
			return m_bIsComplete;
		if(m_pLChild && m_pRChild)
		{
			m_bIsComplete = m_pLChild->isComplete() && m_pRChild->isComplete(); 
			return m_bIsComplete;
		}
		if(m_pLChild)
			m_bIsComplete = m_pLChild->isComplete();
		if(m_pRChild)
			m_bIsComplete = m_pRChild->isComplete();
		return m_bIsComplete;
	}
	virtual void						setComplete(bool bIsComplete = true);
	virtual	void						traverseConds(TraverseCallBack pCallBack);

	virtual PFID						getWaitPFID() ;

	virtual bool						isLeafWaitCond() const {return false;};
	virtual bool						isRootWaitCond() const {if(m_poParent)return false; return true;};
protected:
	WaitCondBase *						m_pLChild;
	WaitCondBase *						m_pRChild;
};

class OrWaitCond : public WaitCondBase {
public:
	OrWaitCond(WaitCondBase *pLChild, WaitCondBase *pRChild)
		: WaitCondBase(NULL)
		, m_pLChild(pLChild)
		, m_pRChild(pRChild)
	{
		if(m_pLChild)
			m_pLChild->setParent(this);
		if(m_pRChild)
			m_pRChild->setParent(this);
	};
	virtual ~OrWaitCond(){
		if(m_pLChild)
			delete m_pLChild;
		if(m_pRChild)
			delete m_pRChild;
	};

	virtual bool						isComplete()
	{
		if(m_bIsComplete)
			return m_bIsComplete;
		if(m_pLChild && m_pRChild)
		{
			m_bIsComplete = m_pLChild->isComplete() || m_pRChild->isComplete(); 
			return m_bIsComplete;
		}
		if(m_pLChild)
			m_bIsComplete = m_pLChild->isComplete();
		if(m_pRChild)
			m_bIsComplete = m_pRChild->isComplete();
		return m_bIsComplete;
	}

	virtual void						setComplete(bool bIsComplete = true);
	virtual	void						traverseConds(TraverseCallBack pCallBack);
	virtual PFID						getWaitPFID();

	virtual bool						isLeafWaitCond()const {return false;};
	virtual bool						isRootWaitCond()const {if(m_poParent)return false; return true;};

protected:
	WaitCondBase *						m_pLChild;
	WaitCondBase *						m_pRChild;
};

class LeafWaitCond : public WaitCondBase{
public:
	LeafWaitCond(const PFID & iPF)
		: WaitCondBase(NULL)
	{
		m_iPFWait.m_iPFID = iPF.m_iPFID;
	};
	virtual ~LeafWaitCond(){};

	virtual bool						isComplete(){return m_bIsComplete;}

	virtual void						setComplete(bool bIsComplete = true);
	virtual	void						traverseConds(TraverseCallBack pCallBack);
	virtual PFID						getWaitPFID();

	virtual bool						isLeafWaitCond()const {return true;} ;
	virtual bool						isRootWaitCond() const {return false;};

protected:
	PFID								m_iPFWait;
};

class AllWaitCond : public WaitCondBase{
public:
	AllWaitCond(const PFID & iPF)
		: WaitCondBase((WaitCondBase*)NULL)
		, m_iCompleteNums(0)
	{
		m_iPFWait.m_iPFID = iPF.m_iPFID;
		//m_iPFWait.m_oDetails.m_iInst = 0xFFFF;
	};
	virtual ~AllWaitCond(){};

	virtual bool						isComplete(){return m_bIsComplete;}
	virtual void						setComplete(bool bIsComplete = true);
	virtual	void						traverseConds(TraverseCallBack pCallBack);

	virtual PFID						getWaitPFID() ;

	virtual bool						isLeafWaitCond()  {return true;};
	virtual bool						isRootWaitCond()  {return false;};

protected:
	PFID								m_iPFWait;
	int									m_iCompleteNums;
};

class AnyWaitCond : public WaitCondBase{
public:	
	AnyWaitCond(const PFID & iPF)
		: WaitCondBase(NULL)
	{
		m_iPFWait.m_iPFID = iPF.m_iPFID;
	};
	virtual ~AnyWaitCond(){};

	virtual bool						isComplete(){return m_bIsComplete;}
	virtual void						setComplete(bool bIsComplete = true);
	virtual	void						traverseConds(TraverseCallBack pCallBack);
	virtual PFID						getWaitPFID();

	virtual bool						isLeafWaitCond() const {return true;};
	virtual bool						isRootWaitCond() const {return false;};

protected:
	PFID								m_iPFWait;
};
#endif
