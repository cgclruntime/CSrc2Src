#include "ParallelPool/ParaPool.h"
#include "ParallelPool/ParaFuncSyn.h"
#include "ParallelPool/FuncContext.h"





ParaPool::ParaPool( int iPoolSize , ParaFuncMgr &oPFMgr)
	: m_iThreadPoolSize(iPoolSize)
	, m_oThreadPool(iPoolSize)
	, m_bIsRunning(true)
	, m_oPFMgr(oPFMgr)
{
	std::vector<int> oWorkerIntestType;
	oWorkerIntestType.push_back(ParaMsgBase::msg_PFReady);
	oWorkerIntestType.push_back(ParaMsgBase::msg_Terminate);
	m_oWorkerPort.regInterestTypes(oWorkerIntestType);

	std::vector<int> oSchedulerType;
	oSchedulerType.push_back(ParaMsgBase::msg_PFSchedule);
	oSchedulerType.push_back(ParaMsgBase::msg_PFOver);
	oSchedulerType.push_back(ParaMsgBase::msg_Terminate);
	m_oSchedulePort.regInterestTypes(oSchedulerType);
	LOG_INFO("ParaPool", "ParaPool(), start tp size:"<<m_iThreadPoolSize);
	m_oThreadPool.schedule(boost::bind(&ParaPool::runScheduler,this));
	for(int i = 1; i<iPoolSize; ++i)
		m_oThreadPool.schedule(boost::bind(&ParaPool::runWorker,this));
}

ParaPool::~ParaPool( void )
{
	//m_bIsRunning = false;
	
	SharedPtr pSend(new AppTerminate());
	for(int i = 0; i<m_iThreadPoolSize; ++i)
		m_oSchedulePort.sendMsg(pSend->getMsgID(),pSend);
	for(int i = 0; i < m_iThreadPoolSize; ++i)
	{
		m_oTerminateSemaphore.P();
	}
}

void ParaPool::schedulePFunc( FuncContext *pFunc )
{
	SharedPtr pSendMsg(new PFReadyMsg(pFunc));
	m_oWorkerPort.sendMsg(pSendMsg->getMsgID(),pSendMsg);

	LOG_INFO("ParaPool", "schedulePFunc() "<<pFunc->m_strFuncName);
}

void ParaPool::scheduleWaitPFunc( FuncContext *pFunc )
{
	SharedPtr pSendMsg(new PFSchedulMsg(pFunc));
	m_oSchedulePort.sendMsg(pSendMsg->getMsgID(),pSendMsg);

	LOG_INFO("ParaPool", "scheduleWaitPFunc() "<<pFunc->m_strFuncName);
}

void ParaPool::runScheduler()
{
	while(m_bIsRunning)
	{
		SharedPtr pRecv;
		int iType = m_oSchedulePort.getMsg(pRecv);
		LOG_INFO("ParaPool", "runScheduler() recv msg: "<<iType);
		struct timeval ts, te;
		struct timezone tz;
		double TMP = 1e6;
		gettimeofday(&ts, &tz);
		
		switch(iType)
		{
		case ParaMsgBase::msg_PFOver:
			handlePFOverMsg(pRecv);
			break;
		case ParaMsgBase::msg_PFSchedule:
			handlePFScheduleMsg(pRecv);
			break;
		case ParaMsgBase::msg_Terminate:
			m_oTerminateSemaphore.V();
			gettimeofday(&te, &tz);
			printf("runScheduler : %.6lf\n", ((te.tv_sec - ts.tv_sec) * TMP + (te.tv_usec - ts.tv_usec)) / TMP); 
			return ;
		default:
			assert(0 && "Unknown msg type!");
		}
		gettimeofday(&te, &tz);
		printf("runScheduler : %.6lf\n", ((te.tv_sec - ts.tv_sec) * TMP + (te.tv_usec - ts.tv_usec)) / TMP); 
	}
}

void ParaPool::runWorker()
{
	//LOG_INFO("aaa", "aaa ");
	while(m_bIsRunning)
	{
		SharedPtr pRecv;
		int iType = m_oWorkerPort.getMsg(pRecv);
		LOG_INFO("ParaPool", "runWorker(), recv msg: "<<iType);
		if(iType == ParaMsgBase::msg_Terminate)
		{
			m_oTerminateSemaphore.V();
			return ;
		}		
		if(iType != ParaMsgBase::msg_PFReady)
		{
			assert(0 && "Unknown msg type!");
		}
		PFReadyMsg *pReadyMsg = (PFReadyMsg *)pRecv.get();
		pReadyMsg->getPFContext()->runPFunc();

		//发送结束的消息
		SharedPtr pSend(new PFOverMsg(pReadyMsg->getPFContext()));
		m_oWorkerPort.sendMsg(pSend->getMsgID(), pSend);
		LOG_INFO("ParaPool", "runWorker(), send msg: "<< pSend->getMsgID());

	}
}

void ParaPool::handlePFOverMsg( SharedPtr & pMsg )
{
	FuncContext *pCtxt = ((PFOverMsg *)pMsg.get())->getPFContext();

	LOG_INFO("ParaPool", "handlePFOverMsg(), handle msg: "<< pCtxt->m_strFuncName);

	//LOG_INFO("ParaPool", "handlePFOverMsg(), try to get lock");
	ParaFuncSyn::getInstance().lock();
	ParaFuncMgr::ParaFuncInfo *pInfo = m_oPFMgr.getPF(pCtxt->m_iFuncID);
	ParaFuncMgr::WaitsContainer *pWaits = m_oPFMgr.getPFWaits(pCtxt->m_iFuncID);
	if(pInfo != NULL)
	{
		pInfo->m_uiState = FuncContext::stat_over;
	}
	if(pWaits != NULL)
	{
		for(int i = 0; i<pWaits->size(); ++i)
		{
			pWaits->at(i)->setComplete(true);
		}
	}
	
	pCtxt->m_uiState = FuncContext::stat_over;

	//LOG_INFO("ParaPool", "handlePFOverMsg(), try to release lock");
	ParaFuncSyn::getInstance().unlock();
}

void ParaPool::handlePFScheduleMsg( SharedPtr  & pMsg )
{
	FuncContext *pCtxt = ((PFSchedulMsg *)pMsg.get())->getPFContext();
	LOG_INFO("ParaPool", "handlePFScheduleMsg(), handle msg: "<< pCtxt->m_strFuncName);


	WaitCondBase *pWaits = pCtxt->getWaitCond();
	if(pWaits->isComplete())
	{
		SharedPtr pSendMsg(new PFReadyMsg(pCtxt));
		m_oWorkerPort.sendMsg(pSendMsg->getMsgID(), pSendMsg);
	}
	else
	{
		m_oSchedulePort.pushBackMsg(pMsg->getMsgID(),pMsg);
	}
}
