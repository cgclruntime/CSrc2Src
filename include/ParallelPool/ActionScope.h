#ifndef _PARALLEL_POOL_ACTION_SCOPE_H
#define _PARALLEL_POOL_ACTION_SCOPE_H
#include "ParallelPool/Types.h"

#include <vector>
#include "ParallelPool/ParaFuncSyn.h"
#include "utl/Log.h"


class FuncContext;

class ActionScope
{
public:
	//************************************
	// Method:    ActionScope
	// FullName:  ActionScope::ActionScope
	// Access:    public 
	// Returns:   
	// Qualifier:��ʼ��mc_iScopeID
	// Parameter: ScopeID iSID
	//************************************
	ActionScope(ScopeID iSID);


	virtual ~ActionScope(void);

	//************************************
	// Method:    exitScope
	// FullName:  ActionScope<N>::exitScope
	// Access:    public 
	// Returns:   void
	// Qualifier: ���������ʱ���øú������ú�������������ڵĺ����Ƿ�ִ����ɣ���ִ������򷵻أ�����ȴ���ֱ���������ڵĺ���ִ����ɣ������������ڵĺ����漰�����ڴ���������������
	//************************************
	void					exitScope();

protected:
	friend class FuncContext;
	friend void parallelFunc(FuncContext *pContext,int iPoolSize);

	//************************************
	// Method:    addPFunc
	// FullName:  ActionScope<N>::addPFunc
	// Access:    protected 
	// Returns:   void
	// Qualifier: ��m_vctPFs������iPF������FuncContext���á�
	// Parameter: const PFID & iPF
	//************************************
	void					addPFunc(FuncContext *pContext);

protected:
	typedef std::vector<FuncContext *>			PFContainer;

	const ScopeID				mc_iScopeID;
	bool						m_bNeedDeconstruce;
	PFContainer					m_vctPFs;
};


#endif
