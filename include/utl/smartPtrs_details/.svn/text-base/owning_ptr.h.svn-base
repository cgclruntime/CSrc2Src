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

#ifndef __UTILS_OWNING_PTR_H
#define __UTILS_OWNING_PTR_H
#include <cassert>

namespace utl
{
	template<class T>
	class OwningPtr
	{
		//forbidden copy construct and assignment
		OwningPtr(const OwningPtr& ){};
		OwningPtr& operator=(const OwningPtr &)
		{
			return *this;
		};
		T *	Ptr;
		public:
			explicit OwningPtr(T *p = 0): Ptr(p){};
			~OwningPtr()
			{
				delete Ptr;
			};
			void	 reset(T *p = 0)
			{
				if(p == Ptr)
				{
					return;
				}
				if(Ptr)
				{
					delete Ptr;
				}
				Ptr = p;
			}
			T &	operator *( ) const 
			{
				assert(Ptr && "cannot dereference null pointer");
				return *Ptr;
			};
			T *	operator ->()  const
			{
				return Ptr;	
			};
			T*	get( )  const
			{ 
				return Ptr;
			};
			operator  bool( )  const 
			{
				return Ptr!=0;
			};
			bool	  operator !( ) const 
			{
				return Ptr == 0;
			};
			void	  swap(OwningPtr &RHS)
			{
				T *Tmp = RHS.Ptr;
				RHS.Ptr = Ptr;
				Ptr = Tmp;
			};

		};//end class OwningPtr;

}//end namespace


#endif

