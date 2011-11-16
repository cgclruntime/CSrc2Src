#include <string>

typedef long long U64;
typedef std::string String;

typedef short int U16;

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

#define get_return_value(eax,edx)	\
	__asm__ __volatile__(		\
	"movl %%eax, %0\n\t"	\
	"movl %%edx, %1"		\
	: "=m" (eax), "=m" (edx)	\
	:		\
	: "memory"	\
	);