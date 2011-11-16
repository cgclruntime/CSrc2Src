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

#ifndef __UTILS_NETWORK_DETAILS_NETWORK_H
#define __UTILS_NETWORK_DETAILS_NETWORK_H

#include "config.h"
#include "exception_base.h"
#include "pkg_base.h"
#include "recv_send_buf.h"

namespace utl
{
	namespace network
	{

		template<typename _socket_type, typename _handler_type = handler
				,class _send_buf_type = default_buf<pkgBase>, class _recv_buf_type = default_buf<pkgBase>
				, class _exception_type = exceptionBase>
		class network
		{	//this template shouldn't never be called.
			public:
				typedef _socket_type				SocketType;
				typedef _handler_type				HandlerType;
				typedef _send_buf_type				SendBufType;
				typedef _recv_buf_type				RecvBufType;
				typedef _exception_type				ExceptionType;
			private:
				network(){////this template shouldn't never be called.
		};

	};//end class network;

		template<typename _handler_type = handler, class _send_buf_type = default_buf<pkgBase>
				, class _recv_buf_type = default_buf<pkgBase>, class _exception_type = exceptionBase>
		class network<utl::network::tcp, _handler_type, _send_buf_type, _recv_buf_type, _exception_type>
		{
			public:
				typedef sock_id							SocketType;
				typedef _handler_type				HandlerType;
				typedef _send_buf_type				SendBufType;
				typedef _recv_buf_type				RecvBufType;
				typedef _exception_type			ExceptionType;
		};//end class network<tcp>

		template<typename _handler_type = handler, class _send_buf_type = default_buf<pkgBase>
				, class _recv_buf_type = default_buf<pkgBase>, class _exception_type = exceptionBase>
		class network<utl::network::udp, _handler_type, _send_buf_type, _recv_buf_type, _exception_type>
		{
			public:
				typedef sock_id							SocketType;
				typedef _handler_type				HandlerType;
				typedef _send_buf_type				SendBufType;
				typedef _recv_buf_type				RecvBufType;
				typedef _exception_type			ExceptionType;
			private:
				network(){};
				network(const network& n){};
				network &	operator = (const network & n){};
			public:
				network(unsigned short iPort){};
				virtual ~network(){};
				virtual int		send(){};
				utl::network::ExceptionType	exception(){};
			protected:
				SocketType			m_oSocket;
				HandlerType		m_oHandler;
				SendBufType		m_oSendBuf;
				RecvBufType		m_oRecvBuf;
				ExceptionType		m_oExcepts;
	};//end class network<udp>

		template<typename _handler_type = handler, class _send_buf_type = default_buf<pkgBase>
				, class _recv_buf_type = default_buf<pkgBase>, class _exception_type = exceptionBase>
		class network<utl::network::unknown, _handler_type, _send_buf_type, _recv_buf_type, _exception_type>
		{
		};//end class network<unknown>

	};//end namespace network;

};//end namespace utl;

#endif