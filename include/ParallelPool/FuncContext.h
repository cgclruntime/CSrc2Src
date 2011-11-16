#ifndef _PARALLEL_POOL_FUNC_CONTEXT_H
#define _PARALLEL_POOL_FUNC_CONTEXT_H

#include "ParallelPool/ActionScope.h"
#include "ParallelPool/Types.h"
#include "utl/Log.h"

#define MAX_ARGS_LEN 512
class FuncContext
{
public:
	enum{
		stat_init = 1,
		stat_ready,
		stat_wait,
		stat_over
	};
public:

	//************************************
	// Method:    FuncContext
	// FullName:  FuncContext::FuncContext
	// Access:    public 
	// Returns:   
	// Qualifier: 初始化相应变量
	// Parameter: ActionScope & oScope
	// Parameter: void * pFuncAddr
	// Parameter: String strPFName
	//************************************
	FuncContext(ActionScope & oScope, void *pFuncAddr, const String& strPFName);
	
	~FuncContext(void);

	//************************************
	// Method:    addWaitCond
	// FullName:  FuncContext::addWaitCond
	// Access:    public 
	// Returns:   void
	// Qualifier: 添加等待条件的二叉树
	// Parameter: WaitCondBase * pWaitConds 等待条件二叉树的根节点指针
	//************************************
	void						addWaitCond(WaitCondBase * pWaitConds);

	//************************************
	// Method:    getWaitCond
	// FullName:  FuncContext::getWaitCond
	// Access:    public 
	// Returns:   WaitCondBase *
	// Qualifier: 返回值可能为NULL
	//************************************
	WaitCondBase *				getWaitCond() const {return m_poWaitConditions;};


	//************************************
	// Method:    runPFunc
	// FullName:  FuncContext::runPFunc
	// Access:    public 
	// Returns:   void
	// Qualifier: 执行该函数
	//************************************
	void						runPFunc();

	U16							getScopeID() const {return m_oScope.mc_iScopeID;}

	PFID &						getPFID(){return m_iFuncID;};
protected:
	friend void parallelFunc(FuncContext *pContext,int iPoolSize);
	friend class ParaFuncMgr;
	friend class PFIDGenerator;
	friend class ParaPool;
	friend class ActionScope;


public:	//以下变量需要不能改变栈结构的前提下访问，所以其权限为public
	unsigned int				m_uiESP1;
	unsigned int				m_uiESP2;
	unsigned int				m_uiEBP1;
	unsigned int				m_uiEBP2;
	char 						m_acArgs[MAX_ARGS_LEN];
	int							m_iArgsLen;

protected:
	std::string					m_strFuncName;
	void *						m_pFuncAddr;
	PFID						m_iFuncID;
	ActionScope &				m_oScope;
	WaitCondBase *				m_poWaitConditions;

	unsigned int				m_uiState;	//并行函数的当前状态
};

#endif
