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
	// Qualifier: ��ʼ����Ӧ����
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
	// Qualifier: ��ӵȴ������Ķ�����
	// Parameter: WaitCondBase * pWaitConds �ȴ������������ĸ��ڵ�ָ��
	//************************************
	void						addWaitCond(WaitCondBase * pWaitConds);

	//************************************
	// Method:    getWaitCond
	// FullName:  FuncContext::getWaitCond
	// Access:    public 
	// Returns:   WaitCondBase *
	// Qualifier: ����ֵ����ΪNULL
	//************************************
	WaitCondBase *				getWaitCond() const {return m_poWaitConditions;};


	//************************************
	// Method:    runPFunc
	// FullName:  FuncContext::runPFunc
	// Access:    public 
	// Returns:   void
	// Qualifier: ִ�иú���
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


public:	//���±�����Ҫ���ܸı�ջ�ṹ��ǰ���·��ʣ�������Ȩ��Ϊpublic
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

	unsigned int				m_uiState;	//���к����ĵ�ǰ״̬
};

#endif
