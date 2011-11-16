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

#ifndef __UTILS_NETWORK_DETAILS_CONFIG_H
#define __UTILS_NETWORK_DETAILS_CONFIG_H

#if defined WIN32 || defined _WIN32
#include <WinSock2.h>
#define SOCK_VERSION1 2
#define SOCK_VERSION2 2

typedef SOCKET  sock_id;
#else
#endif

namespace utl
{
	namespace network
	{
		typedef void (*handler)(const void *buf, int iBufLen);
		class tcp{};
		class udp{};
		class unknown{};
	};//end of namespace network

};//end of namespace utl

#endif


