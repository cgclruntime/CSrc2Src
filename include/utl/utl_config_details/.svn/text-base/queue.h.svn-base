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

#ifndef __UTILS_QUEUE_H
#define __UTILS_QUEUE_H

#define MULTI_QUEUE_LOCK(_ty,_f)	 \
{  \
	m_oMutex.lock( );	\
	_ty temp = m_oQueue._f( );  	\
	m_oMutex.unlock( );	 \
	return temp;  \
}

#include <queue>
namespace utl
{
	namespace details
	{
		template<class T>
		class single_thrd_queue : public std::queue<T>
		{
			public:
				void		lockQueue( ){ };
				void		unlockQueue( ){ };
	    };

	    template<class T>
	    class multi_thrd_queue : public std::queue<T>
		{
			private:
				std::queue<T>					m_oQueue;
				mutable utl::Mutex			m_oMutex;
				//Fix it: copy constructer and assignment overload for m_oMutex
				multi_thrd_queue(const multi_thrd_queue & q){ };
				multi_thrd_queue &	operator =(const multi_thrd_queue & q){ };
			public:
				multi_thrd_queue(): m_oMutex(), m_oQueue( ){ };
				virtual ~multi_thrd_queue(){};
			    void	 lockQueue( )
				{
					m_oMutex.lock( );
				}
				void	 unlockQueue( )
				{
					m_oMutex.unlock( );
				}

		};//end multi_thrd_queue

	}//end namespace detail

}//end namespace utl


#endif

