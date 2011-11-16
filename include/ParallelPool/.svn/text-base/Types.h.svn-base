#ifndef _PARALLEL_POOL_TYPES_H
#define _PARALLEL_POOL_TYPES_H

#include <string>

typedef long long U64;
typedef std::string String;

typedef short int	U16;



typedef union {
	U64				m_iPFID;
	struct{
		U16			m_iScope;		//按照作用域编号
		U16			m_iFunc;		//按照函数编号
		U16			m_iPara;		//按照并行函数变量编号
		U16			m_iInst;		//并行实例个数，
	}m_oDetails;
}PFID;

typedef U16			ScopeID;

struct ltPfid{                                                  //比较两个PFID大小
	bool operator()( PFID p1, PFID p2) const
	{
		p1.m_oDetails.m_iInst = p2.m_oDetails.m_iInst = 0;
		return p1.m_iPFID < p2.m_iPFID;
	}
};
class WaitCondBase;
typedef void ( * TraverseCallBack)(WaitCondBase *);

#define get_stack_info(esp,ebp)	\
	__asm__ __volatile__(		\
	"movl %%esp, %0\n\t"	\
	"movl %%ebp, %1"		\
	: "=m" (esp), "=m" (ebp)	\
	:		\
	: "memory"	\
	);

#define set_stack_info(esp,ebp) \
	__asm__ __volatile__(		\
	"movl %0, %%esp\n\t"		\
	"movl %1, %%ebp"			\
	:							\
	: "m"(esp), "m"(ebp)	\
	);

#endif

