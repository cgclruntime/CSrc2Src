#ifndef _PARALLEL_POOL_PFID_GENERATOR_H
#define _PARALLEL_POOL_PFID_GENERATOR_H
#include <map>
#include "ParallelPool/Types.h"
#include "utl/Log.h"

class FuncContext;
class PFIDGenerator
{
public:
	PFIDGenerator(void);
	~PFIDGenerator(void);

	void							clearScopeData(U16 iScopeID);

	PFID							generatePFID(FuncContext * pCtxt);

protected:
	typedef std::map<String, U16>			Para2IDContainer;		//map<并行函数名，id>
	typedef struct{
		U16					m_iFuncID;
		Para2IDContainer *	m_pParas;
	}FuncAndParas;
	typedef std::map<void *, FuncAndParas *>	FuncContainer;
	typedef struct{
		U16					m_iScopeID;
		FuncContainer *		m_pFuncs;
	}ScopeAndFuncs;
	typedef std::map<U16, ScopeAndFuncs *>			ScopeContainer;
	
	ScopeContainer			m_oPFIDs;

};

#endif
