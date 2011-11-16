#ifndef _PARALLEL_POOL_PARA_MSG_H
#define _PARALLEL_POOL_PARA_MSG_H

#include "Types.h"
#include "utl/Log.h"

class FuncContext;



class ParaMsgBase
{
public:
	enum{
		msg_PFSchedule,
		msg_PFOver,
		msg_PFReady,
		msg_Terminate
	};
protected:
	ParaMsgBase(int iMsgID)
		: m_iMsgID(iMsgID){};
public:
	virtual ~ParaMsgBase(){};

	int				getMsgID() const {return m_iMsgID;};
protected:
	int				m_iMsgID;
};

class PFSchedulMsg : public ParaMsgBase
{
public:
	PFSchedulMsg(FuncContext *pPFCtxt)
		: ParaMsgBase(ParaMsgBase::msg_PFSchedule)
		, m_pPFCtxt(pPFCtxt){};
	virtual ~PFSchedulMsg(){};

	FuncContext *			getPFContext() const {return m_pPFCtxt;};
protected:
	FuncContext *			m_pPFCtxt;
};

class PFOverMsg : public ParaMsgBase
{
public:
	PFOverMsg(FuncContext *pPFCtxt)
		: ParaMsgBase(ParaMsgBase::msg_PFOver)
		, m_pPFCtxt(pPFCtxt){};
	virtual ~PFOverMsg(){};

	FuncContext *			getPFContext() const {return m_pPFCtxt;};
protected:
	FuncContext *			m_pPFCtxt;
};

class PFReadyMsg : public ParaMsgBase
{
public:
	PFReadyMsg(FuncContext * pPFCtxt)
		: ParaMsgBase(ParaMsgBase::msg_PFReady)
		, m_pPFCtxt(pPFCtxt){};
	virtual ~PFReadyMsg(){};

	FuncContext *			getPFContext() const {return m_pPFCtxt;};
protected:
	FuncContext *			m_pPFCtxt;
};
class AppTerminate : public ParaMsgBase
{
public:
	AppTerminate()
		: ParaMsgBase(ParaMsgBase::msg_Terminate)
	{
	};
	virtual ~AppTerminate(){};

protected:
};
#endif
