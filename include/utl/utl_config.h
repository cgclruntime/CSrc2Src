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

#ifndef __UTILS_UTL_CONFIG_H
#define __UTILS_UTL_CONFIG_H

#include "utl_config_details/reference_count.h"
#include "utl_config_details/queue.h"

namespace utl
{
	//单线程下数据类型的定义
	struct single_thrd
	{
		typedef utl::details::single_thrd_reference_count		reference_count;

		template <class _Ty>
		class queue : public utl::details::single_thrd_queue<_Ty>{ };

		//Just adapter
		class Mutex
		{
			public:
				void		lock(){};
				void		unlock(){};
		};
		class Guard
		{
			public:
				explicit Guard(Mutex & ){};
				~Guard(){};
		};
	};

	//多线程下数据类型的定义
	struct multi_thrd
	{
		typedef utl::details::multi_thrd_reference_count	 reference_count;
		template <class _Ty>
		class queue : public utl::details::multi_thrd_queue<_Ty>{ };

		typedef utl::Mutex	 Mutex;
		typedef utl::Guard	 Guard;
	};

}
#endif

