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

#ifndef __UTILS_SHARED_PTR_H
#define __UTILS_SHARED_PTR_H
#include "../Threads.h"
#include "owning_ptr.h"
#include "../utl_config.h"

namespace utl
{
	template <class T, class thrd_attr = multi_thrd>
	class SharedPtr
	{
		private:
			typedef typename thrd_attr::reference_count	reference_count;

		public:
			explicit SharedPtr(T *p = 0): Ptr(p)
			{
				if(p)
				{
					m_pReferCount = new reference_count();
					assert(m_pReferCount && "bad malloc");
					m_pReferCount->increment();
				}
				else
				{
					m_pReferCount = 0;
				}
			};

			SharedPtr(const SharedPtr<T, thrd_attr> &ptr): Ptr(ptr.Ptr), m_pReferCount(ptr.m_pReferCount)
			{
				if(Ptr)
			    {
				assert(m_pReferCount && "cannot dereference null pointer");
				m_pReferCount->increment();
				}
			};

			~SharedPtr()
			{
				if(Ptr)
				{
					assert(m_pReferCount && "cannot dereference null pointer");
					if(m_pReferCount->decrement() == 0)
					{
						delete Ptr;
						delete m_pReferCount;
					}
				}
			}

			SharedPtr<T, thrd_attr> &	operator =(const SharedPtr<T, thrd_attr> &ptr)
			{
				if(&ptr == this)
				{
					return *this;
				}
				if(ptr.Ptr == Ptr)
				{
					assert(ptr.m_pReferCount == m_pReferCount && "same ptr with different reference count!");
					return *this;
				}
				if(Ptr)
				{
					assert(m_pReferCount && "unexpected null pointer");
					int temp = m_pReferCount->decrement();
					if(temp ==0)
					{
						delete Ptr;
					}
				}
				Ptr = ptr.Ptr;
				m_pReferCount = ptr.m_pReferCount;
				if(m_pReferCount)	m_pReferCount->increment();
				return *this;
	}

			T *	operator ->( ) const
			{
				return Ptr;
			};

			T&	operator *( ) const
			{
				assert(Ptr &&"cannot dereference null pointer");
				return *Ptr;
			};
			T *	get() const { return Ptr;};
			void	 swap(SharedPtr<T, thrd_attr> & ptr)
			{
				T *temp = Ptr;
				Ptr = ptr.Ptr;
				ptr.Ptr = temp;
		
				reference_count *pTemp = m_pReferCount;
				m_pReferCount = ptr.m_pReferCount;
				ptr.m_pReferCount = pTemp;
			}

		private:
			T *	 Ptr;
			reference_count *	m_pReferCount;

	};//end class SharedPtr

}//end namespace utl

#endif
