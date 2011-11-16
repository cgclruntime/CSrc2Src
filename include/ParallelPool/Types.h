#ifndef _PARALLEL_POOL_TYPES_H
#define _PARALLEL_POOL_TYPES_H

#include <string>

typedef long long U64;
typedef std::string String;

typedef short int	U16;



typedef union {
	U64				m_iPFID;
	struct{
		U16			m_iScope;		//������������
		U16			m_iFunc;		//���պ������
		U16			m_iPara;		//���ղ��к����������
		U16			m_iInst;		//����ʵ��������
	}m_oDetails;
}PFID;

typedef U16			ScopeID;

struct ltPfid{                                                  //�Ƚ�����PFID��С
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

