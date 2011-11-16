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
#ifndef __UTILS_NETWORK_DETAILS_SOCKET_BASE_H
#define __UTILS_NETWORK_DETAILS_SOCKET_BASE_H

namespace utl
{
	namespace network
	{
		class NetAddrV4
		{
			public:
				NetAddrV4(){};
				NetAddrV4(const NetAddrV4 & addr){};
				NetAddrV4(unsigned short iPort){};	//for local addr;
				template<int N>
				NetAddrV4(const char (&ip)[N], unsigned short iPort);
				NetAddrV4(unsigned int ip, unsigned short iPort);
				NetAddrV4 &	operator = (const NetAddrV4 &addr){};

				std::string	toString() const;

				const unsigned int &		ip() const{return m_uiIP;};
				const unsigned short &		port() const {return m_uiPort;};

			private:
				unsigned int		m_uiIP;
				unsigned short	m_uiPort;			
		};//end class NetAddrV4;

		class SocketBase
		{
			protected:
				SocketBase();
			public:
				virtual ~SocketBase(){};
				virtual int		send(const NetAddrV4& toAddr, void *pBuf, int iLen) = 0;
				virtual int		recv(NetAddrV4& fromAddr, void* pBuf, int &iLen) = 0;
				virtual int		bind(const NetAddrV4 & addr) = 0;
				virtual int		listen() = 0;

				virtual utl::network::sock_id &	socket()
				{
					return m_oSocket;
				};
			protected:
				utl::network::sock_id	m_oSocket;
		};//end class SocketBase;

		class UdpSocket : public SocketBase
		{
		};//end class UdpSocket;

	};//end namespace network

};//end namespace utl;
#endif
