/*************************************************************************/
/*                                                                       */
/*  Copyright (c) 2011 Athrun Arthur	                                 */
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

#ifndef __UTILS_THREAD_DETAILS_THREAD_WORK_H
#define __UTILS_THREAD_DETAILS_THREAD_WORK_H
#if defined WIN32 || defined _WIN32
#include <Windows.h>

#else
#endif

namespace utl
{
	template<class _Tx>
	class ThreadWork;

	#if defined WIN32 || defined _WIN32
		template < class _Tx>
		DWORD WINAPI __ThreadProc__( LPVOID lpParam)
		{
			((ThreadWork<_Tx> *)lpParam)->run_thread();
			return 0;
		};

		template< class _Tx>
		class ThreadWork
		{
			protected:
				ThreadWork(const ThreadWork<_Tx> & m){};
				ThreadWork<_Tx> &	operator = (const ThreadWork<_Tx> & m){};

			public:
				explicit ThreadWork(_Tx f): m_oFuncObject(f)
				{
					m_hThread = ::CreateThread(NULL, 0,__ThreadProc__<_Tx>, this,0,&m_dwThreadID);
					if(m_hThread == NULL)
					{
						assert(0 &&"ThreadWork::CreateThread Failed!");
						exit(0);
					}
				};
				virtual ~ThreadWork(){};

				bool	 join()
				{
					::WaitForMultipleObjects(1, &m_hThread,TRUE, INFINITE);
					return true;
				};
			protected:
				friend DWORD WINAPI __ThreadProc__<_Tx>( LPVOID lpParam);
				virtual void	run_thread()
				{
					m_oFuncObject();
				};

				_Tx	&			m_oFuncObject;
				HANDLE		m_hThread;
				DWORD		m_dwThreadID;

	};//end class thread_work;

	#else

	#endif

};//end namespace utl
#endif
