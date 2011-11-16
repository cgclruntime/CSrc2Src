#ifndef _PARALLEL_POOL_PARA_POOL_H
#define _PARALLEL_POOL_PARA_POOL_H

#include "utl/Msg.h"
#include "utl/SmartPtrs.h"
#include "utl/Threads.h"
#include "ParallelPool/ParaFuncMgr.h"
#include "ParallelPool/ParaMsg.h"
#include "threadpool.hpp"


class FuncContext;

class ParaPool
{
public:
	typedef boost::threadpool::pool			TPool;
	typedef utl::SharedPtr<ParaMsgBase, utl::multi_thrd>	SharedPtr;
	typedef utl::MsgPort< ParaMsgBase, utl::multi_thrd>		MPort;

public:
	ParaPool(int iPoolSize, ParaFuncMgr &oPFMgr);
	~ParaPool(void);

	//************************************
	// Method:    schedulePFunc
	// FullName:  ParaPool<N>::schedulePFunc
	// Access:    public 
	// Returns:   void
	// Qualifier: 将一个直接就绪的任务放到工作线程中运行
	//************************************
	void							schedulePFunc(FuncContext *pFunc);

	//************************************
	// Method:    scheduleWaitPFunc
	// FullName:  ParaPool<N>::scheduleWaitPFunc
	// Access:    public 
	// Returns:   void
	// Qualifier: 将一个可能需要等待的任务放到调度线程中运行
	// Parameter: FuncContext * pFunc
	//************************************
	void							scheduleWaitPFunc(FuncContext *pFunc);

protected:

	//************************************
	// Method:    runScheduler
	// FullName:  ParaPool<N>::runScheduler
	// Access:    protected 
	// Returns:   void
	// Qualifier: 调度线程的回调函数
	//************************************
	void							runScheduler(); 


	//************************************
	// Method:    runWorker
	// FullName:  ParaPool<N>::runWorker
	// Access:    protected 
	// Returns:   void
	// Qualifier: 一个工作线程的回调函数
	//************************************
	void							runWorker();


	void							handlePFOverMsg(SharedPtr & pMsg);

	void							handlePFScheduleMsg(SharedPtr & pMsg);
protected:
	

	TPool							m_oThreadPool;
	MPort							m_oSchedulePort;
	MPort							m_oWorkerPort;

	bool							m_bIsRunning;
	int								m_iThreadPoolSize;

	ParaFuncMgr&					m_oPFMgr;
	utl::Semaphore 					m_oTerminateSemaphore;

};


#endif
