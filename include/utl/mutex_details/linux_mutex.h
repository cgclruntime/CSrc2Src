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

#ifndef __UTILS_MUTEX_DETAILS_LINUX_MUTEX_H
#define __UTILS_MUTEX_DETAILS_LINUX_MUTEX_H

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <cassert>

#define EXCEPTION( bVal, reason ) \
	{ \
		if(bVal) \
		{	\
			assert(0 && reason);	\
			exit(0);	\
		} \
	 } 

namespace utl
{
	///class Mutex///////////////////////////////////////////////////////////////////////
	class Mutex
	{
		private:
			Mutex(const Mutex&m){};
			Mutex &		operator = (const Mutex&m){};
		public:
			Mutex()
			{
				int res = pthread_mutex_init(&m_cs, 0);
				EXCEPTION(res,"pthread_mutex_init failed!");
			};
			~Mutex()
			{
				int res = pthread_mutex_destroy(&m_cs);
				EXCEPTION(res,"pthread_mutex_destroy failed!");
			};
			void	lock()
			{
				int res = pthread_mutex_lock(&m_cs);
				EXCEPTION(res, "pthread_mutex_lock failed!");
			};
			void	unlock()
			{
				int res = pthread_mutex_unlock(&m_cs);
				EXCEPTION(res, "pthread_mutex_unlock failed!");
			};
		protected:
			pthread_mutex_t m_cs;
	};//end class Mutex

	//class Semaphore////////////////////////////////////////////////////////////////////////
	class Semaphore
	{
		//用于多个线程的P，V操作
		private:
			Semaphore(const Semaphore & s){};
			Semaphore &	operator =(const Semaphore &s){};
		public:
			Semaphore(int iInitVal = 0)
			{
				int res = sem_init(&m_sem,0,iInitVal);
				EXCEPTION(res,"sem_init failed!");
			};
			~Semaphore()
			{
				int res = sem_destroy(&m_sem);
				EXCEPTION(res,"sem_destroy failed!");
			};
		
			inline void 	P( )
			{
				int res = sem_wait(&m_sem);
				EXCEPTION(res,"sem_wait failed!");
			};
			inline void	V( )
			{
				int res = sem_post(&m_sem);
				EXCEPTION(res,"sem_post failed!");
			};

		protected:
			sem_t			m_sem;
	};//end class Semaphore

	//class BoolSemaphore////////////////////////////////////////////////////////////////////////
	class BoolSemaphore
	{
		//只能用于两个线程，其中一个线程进行P操作，另一个线程进行V操作；
		private:
			BoolSemaphore(const BoolSemaphore& b){};
			BoolSemaphore &	operator =(const BoolSemaphore& b){};
		public:
			BoolSemaphore(int iInitVal = 0): m_iResNum(iInitVal), m_bCondFlag(false)
			{
				pthread_mutex_init(&m_cs,0);
				pthread_cond_init(&m_cond, 0);
			};
			~BoolSemaphore()
			{
				pthread_mutex_destroy(&m_cs);
				pthread_cond_destroy(&m_cond);
			};

			void		P()
			{
				pthread_mutex_lock(&m_cs);
				int temp = m_iResNum --;
				pthread_mutex_unlock(&m_cs);
				if(temp<0)
				{
					if(!m_bCondFlag)
					{
						m_bCondFlag = true;
					}
					pthread_cond_wait(&m_cond,&m_cs);
				}
			};
			void		V( )
			{
				pthread_mutex_lock(&m_cs);
				int temp = m_iResNum ++;
				pthread_mutex_unlock(&m_cs);
				if(m_bCondFlag)
				{
					pthread_cond_signal(&m_cond);
				}
			};

		protected:
			bool				m_bCondFlag;
			int				m_iResNum;
			pthread_cond_t		m_cond;
			pthread_mutex_t		m_cs;

	};//end BoolSemaphore

};//end namespace utl

#undef EXCEPTION
#endif

