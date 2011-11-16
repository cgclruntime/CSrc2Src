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

#ifndef __UTILS_NETWORK_DETAILS_RECV_SEND_BUF_H
#define __UTILS_NETWORK_DETAILS_RECV_SEND_BUF_H
#include "pkg_base.h"
#include <queue>
#include "../Mutex.h"
namespace utl
{
	namespace network
	{
		template<class _Ty = pkgBase>
		class default_buf : public std::queue<_Ty>
		{
			public:
				void					lock_queue(){m_oMutex.lock();}
				void					unlock_queue(){m_oMutex.unlock();}
			protected:
				utl::Mutex				m_oMutex;

		};//end class default_buf

	};//end namespace network

};//end namespace utl;

#endif