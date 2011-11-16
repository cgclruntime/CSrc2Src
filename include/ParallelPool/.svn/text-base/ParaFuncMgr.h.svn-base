#ifndef _PARALLEL_POOL_PARA_FUNC_MGR_H
#define _PARALLEL_POOL_PARA_FUNC_MGR_H

#include <map>
#include <vector>
#include <list>
#include "utl/Exception.h"
#include "ParallelPool/Types.h"
#include "ParallelPool/WaitConds.h"
#include "ParallelPool/PFIDGenerator.h"
#include "utl/Log.h"


class ParaFuncMgr
{
public:


	struct ParaFuncInfo{
		ParaFuncInfo(){
			LOG_INFO("ParaFuncInfo", "construct");
		};
		virtual ~ParaFuncInfo()
		{
			LOG_INFO("ParaFuncInfo", "deconstruct");
		}
		PFID			m_iParaFuncID;		//并行函数ID
		WaitCondBase *	m_poWaitConds;		//并行函数的等待条件
		FuncContext *	m_poContext;		//并行函数的上下文
		unsigned int	m_uiState;			
	} ;				//并行函数信息

	typedef std::vector<WaitCondBase *>				WaitsContainer;		//等待节点集

	typedef std::map<PFID, WaitsContainer *,ltPfid>		PFWaitsContainer;	//等待PFID函数执行完成的节点集

	typedef std::map<PFID, ParaFuncInfo *, ltPfid>			ParaFuncContainer;	//所有函数的信息集

protected:
	ParaFuncMgr(void);
public:
	~ParaFuncMgr(void);

	static ParaFuncMgr &						getInstance();

	static void									traverseSetWaitsCond(WaitCondBase *pWaitCond);

	//************************************
	// Method:    getOrInsertPF
	// FullName:  ParaFuncMgr::getOrInsertPF
	// Access:    public 
	// Returns:   FuncContext *
	// Qualifier: 查找或者插入一个函数的信息，插入函数信息时需要生成相应的ID
	// Parameter: FuncContext * pCtxt
	//************************************
	ParaFuncInfo *								getOrInsertPF(FuncContext *pCtxt);

	//************************************
	// Method:    getPF
	// FullName:  ParaFuncMgr::getPF
	// Access:    public 
	// Returns:   ParaFuncInfo *
	// Qualifier: 根据PFID查找并行函数的信息
	// Parameter: const PFID & iPF
	//************************************
	ParaFuncInfo *								getPF(const PFID &iPF);

	//************************************
	// Method:    getPFWaits
	// FullName:  ParaFuncMgr::getPFWaits
	// Access:    public 
	// Returns:   WaitsContainer *
	// Qualifier: 得到PFID对应的等待节点
	// Parameter: const PFID & iPF
	//************************************
	WaitsContainer *							getPFWaits(const PFID &iPF);

	void										clearScope(U16 iScopeID);
protected:
	//************************************
	// Method:    generatePFID
	// FullName:  ParaFuncMgr::generatePFID
	// Access:    protected 
	// Returns:   void
	// Qualifier: 为并行函数生成ID
	// Parameter: FuncContext * pCtxt
	//************************************


protected:

	PFWaitsContainer				m_mapPFWaits;
	ParaFuncContainer				m_mapAllPFs;

	static ParaFuncMgr *			sv_pInstance;
	PFIDGenerator					m_oPFIDGenerator;
};

#endif
