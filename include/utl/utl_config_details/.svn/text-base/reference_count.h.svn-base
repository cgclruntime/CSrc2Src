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

#ifndef __UTILS_REFERENCE_COUNT_H
#define __UTILS_REFERENCE_COUNT_H

#include "../mutex_details/mutex.h"
namespace utl
{
	namespace details
	{
		class multi_thrd_reference_count
		{
			private:
				explicit multi_thrd_reference_count(const multi_thrd_reference_count& ){};
				multi_thrd_reference_count &	operator =(const multi_thrd_reference_count &m){return *this;};
			public:
				multi_thrd_reference_count(): m_oMutex(), m_iReferenceCount(0){};
				~multi_thrd_reference_count(){};

				int	increment(const int i = 1)
				{
					int temp;
					m_oMutex.lock();
					m_iReferenceCount +=i;
					temp = m_iReferenceCount;
					m_oMutex.unlock();
					return temp;
				}
				int	decrement(const int i = 1)
				{
					int temp;
					m_oMutex.lock();
					m_iReferenceCount -=i;
					temp = m_iReferenceCount;
					m_oMutex.unlock();
					return temp;
				}
				int	current_count() const
				{
					int temp;
					m_oMutex.lock();
					temp = m_iReferenceCount;
					m_oMutex.unlock();
					return temp;
				}
			private:
				mutable Mutex	m_oMutex;
				int	m_iReferenceCount;
		};//end class multi_thrd_reference_count

		class single_thrd_reference_count
		{
			private:
				explicit single_thrd_reference_count(const single_thrd_reference_count& m){};
				single_thrd_reference_count &		operator =(const single_thrd_reference_count &m){return *this;};
			public:
				single_thrd_reference_count(): m_iReferenceCount(0){};
				~single_thrd_reference_count(){};

				inline int		increment(const int i = 1)
				{
					m_iReferenceCount +=i;
					return m_iReferenceCount;
				}
				inline int		decrement(const int i = 1)
				{
					m_iReferenceCount -=i;
					return m_iReferenceCount;
				}
				inline int		current_count() const
				{
					return m_iReferenceCount;
				}

			private:
				mutable Mutex	m_oMutex;
				int		m_iReferenceCount;
		};//end class single_thrd_reference_count

	}//end namespace details

}//end namespace utl

#endif



