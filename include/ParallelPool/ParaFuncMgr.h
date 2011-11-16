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
		PFID			m_iParaFuncID;		//���к���ID
		WaitCondBase *	m_poWaitConds;		//���к����ĵȴ�����
		FuncContext *	m_poContext;		//���к�����������
		unsigned int	m_uiState;			
	} ;				//���к�����Ϣ

	typedef std::vector<WaitCondBase *>				WaitsContainer;		//�ȴ��ڵ㼯

	typedef std::map<PFID, WaitsContainer *,ltPfid>		PFWaitsContainer;	//�ȴ�PFID����ִ����ɵĽڵ㼯

	typedef std::map<PFID, ParaFuncInfo *, ltPfid>			ParaFuncContainer;	//���к�������Ϣ��

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
	// Qualifier: ���һ��߲���һ����������Ϣ�����뺯����Ϣʱ��Ҫ������Ӧ��ID
	// Parameter: FuncContext * pCtxt
	//************************************
	ParaFuncInfo *								getOrInsertPF(FuncContext *pCtxt);

	//************************************
	// Method:    getPF
	// FullName:  ParaFuncMgr::getPF
	// Access:    public 
	// Returns:   ParaFuncInfo *
	// Qualifier: ����PFID���Ҳ��к�������Ϣ
	// Parameter: const PFID & iPF
	//************************************
	ParaFuncInfo *								getPF(const PFID &iPF);

	//************************************
	// Method:    getPFWaits
	// FullName:  ParaFuncMgr::getPFWaits
	// Access:    public 
	// Returns:   WaitsContainer *
	// Qualifier: �õ�PFID��Ӧ�ĵȴ��ڵ�
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
	// Qualifier: Ϊ���к�������ID
	// Parameter: FuncContext * pCtxt
	//************************************


protected:

	PFWaitsContainer				m_mapPFWaits;
	ParaFuncContainer				m_mapAllPFs;

	static ParaFuncMgr *			sv_pInstance;
	PFIDGenerator					m_oPFIDGenerator;
};

#endif
