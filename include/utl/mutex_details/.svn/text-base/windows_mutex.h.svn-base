/*************************************************************************/
/*                                                                       */
/*  Copyright (c) 2010 Athrun Arthur	                                 */
/*                                                                       */
/*  All rights reserved.                                                 */
/*                                                                       */
/*  Permission is given to use, copy, and modify this software for any   */
/*  non-commercial purpose as long as this copyright notice is not       */
/*  removed.  All other uses, including redistribution in whole or in    */
/*  part, are forbidden without prior written permission.                */
/*                                                                       */
/*  This software is provided with absolutely no warranty and no         */
/*  support.                                                             */
/*                                                                       */
/*************************************************************************/

#ifndef __UTILS_MUTEX_DETAILS_WINDOWS_MUTEX_H
#define __UTILS_MUTEX_DETAILS_WINDOWS_MUTEX_H

#define _WINDOWS_MUTEX_DEATILS_MAX_SEMAPHORE_COUNT 0xFFFFFFFF

#include <windows.h>
#include <cassert>

#define EXCEPTION( bVal, reason ) \
{ \
	if(bVal) {	\
		assert(0 && reason);	\
		exit(0);	\
	} \
}

namespace utl
{
	class Mutex
	{
		private:
			//forbidden
			Mutex(const Mutex&){ };
			Mutex &	 operator = (const Mutex& m)
			{
				if(&m == this)	return *this;
				return *this;
			};

		public:
			Mutex()
			{
				InitializeCriticalSection(&m_cs);
			};
			~Mutex()
			{
				DeleteCriticalSection(&m_cs);
			};
			void	lock()
			{
				EnterCriticalSection(&m_cs);
			};
			void	unlock()
			{
				LeaveCriticalSection(&m_cs);
			};

		protected:
			CRITICAL_SECTION m_cs;
};//end class Mutex

//////////////////////////////////////////////////////////////////////////
    class Semaphore
    {
	    private:
		    Semaphore(const Semaphore & s){};
		    Semaphore &	operator =(const Semaphore &s){};

	    public:
		    Semaphore(int iInitVal = 0)
		    {
			    m_hSem = CreateSemaphore(NULL,iInitVal,_WINDOWS_MUTEX_DEATILS_MAX_SEMAPHORE_COUNT, NULL);
			    EXCEPTION(m_hSem!=NULL,"CreateSemaphore failed!")
		    };
		    ~Semaphore()
		    {
			    CloseHandle(m_hSem);
		    };

		    inline void	P()
			{
				WaitForSingleObject(m_hSem,INFINITE);
			};
		    inline void	V()
			{
				ReleaseSemaphore(m_hSem,1,NULL);
			};

	    protected:
	     	HANDLE	 m_hSem;
	};//end class Semaphore;

}//end namespace utl

#undef EXCEPTION
#endif

