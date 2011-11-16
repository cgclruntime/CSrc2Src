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

#ifndef __UTILS_MUTEX_H
#define __UTILS_MUTEX_H

#if defined WIN32 || defined _WIN32
	#include "windows_mutex.h"
#else
	#include "linux_mutex.h"
#endif

namespace utl
{
	class Guard
	{
		private:
			Guard(): m_pMutex(0){};
			Guard(const Guard&): m_pMutex(0){};
			Guard &	operator = (const Guard &m){return *this;};
		public:
			explicit Guard(Mutex & m): m_pMutex(&m){m_pMutex->lock();};
			~Guard(){m_pMutex->unlock();m_pMutex = 0;};
		protected:
			utl::Mutex *		m_pMutex;
	};//end class Guard

}//end namespace utl

#endif
