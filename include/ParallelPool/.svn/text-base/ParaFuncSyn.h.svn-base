#ifndef _PARALLEL_POOL_PARA_FUNC_SYN_H
#define _PARALLEL_POOL_PARA_FUNC_SYN_H

#include "utl/Threads.h"
#include "utl/Log.h"

class ParaFuncSyn{
protected:
	ParaFuncSyn(){};
public:
	~ParaFuncSyn(){};

	static	ParaFuncSyn &				getInstance(){return sv_oInstance;};

	void								lock(){
		m_oMutex.lock();

	};

	void								unlock(){
		m_oMutex.unlock();
	};
protected:
	utl::Mutex							m_oMutex;
	static ParaFuncSyn					sv_oInstance;
};


#endif


