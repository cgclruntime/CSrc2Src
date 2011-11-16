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
	// Qualifier:初始化mc_iScopeID
	// Parameter: ScopeID iSID
	//************************************
	ActionScope(ScopeID iSID);


	virtual ~ActionScope(void);

	//************************************
	// Method:    exitScope
	// FullName:  ActionScope<N>::exitScope
	// Access:    public 
	// Returns:   void
	// Qualifier: 作用域结束时调用该函数，该函数检查作用域内的函数是否执行完成，若执行完成则返回，否则等待，直到作用域内的函数执行完成，并对作用域内的函数涉及到的内存做最后的清理工作。
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
	// Qualifier: 在m_vctPFs中增加iPF，仅供FuncContext调用。
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
