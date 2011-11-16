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

#ifndef __UTILS_NETWORK_DETAILS_UDP_SENDER_RECVER_H
#define __UTILS_NETWORK_DETAILS_UDP_SENDER_RECVER_H

#include "../Mutex.h"
#include "config.h"
#include "../Exception.h"
#include "pkg_base.h"
#include "recv_send_buf.h"

#define MAX_SEND_BUF_SIZE 1024*16
namespace utl
{
	namespace network
	{
		class SenderRecverCoordinator
		{		//用于调整sender与recver之间的共享关系
			public:
				SenderRecverCoordinator(bool bWritableFlag): m_bWritableFlag(bWritableFlag)
				{
					m_hWritableEvent = ::CreateEvent(NULL,TRUE,TRUE,NULL);
					if(m_hWritableEvent == 0)
					{
						m_oExceptions.addInfo("SenderRecverCoordinator::SenderRecverCoordinator, CreateEvent return NUll");
						exit(0);
					}
					m_hSendBufSemphore = ::CreateSemaphore(NULL,0,MAX_SEND_BUF_SIZE,NULL);
					if(m_hSendBufSemphore == 0)
					{
						m_oExceptions.addInfo("SenderRecverCoordinator::SenderRecverCoordinator, CreateSemaphore return Null");
						exit(0);
					}
				};
			
				inline void	setWritableFlag(bool bWritableFlag)
				{
					m_bWritableFlag = bWritableFlag;
				};

				inline bool	getWritableFlag()
				{
					return m_bWritableFlag;
				};

				inline  void	PSendBuf()
				{
					::WaitForSingleObject(m_hSendBufSemphore,INFINITE);
				};
				inline  void	VSendBuf()
				{
					::ReleaseSemaphore(m_hSendBufSemphore, 1,NULL);
				};
			protected:
				utl::Mutex			m_oMutexForFlags;
				bool			m_bWritableFlag;
				utl::Exception		m_oExceptions;
			public:
#if defined WIN32 || defined _WIN32
		HANDLE			m_hWritableEvent;
		HANDLE			m_hSendBufSemphore;
#else
#endif
		};

	#if defined WIN32 || defined _WIN32
		class UDPSender
		{
			public:
				UDPSender(SenderRecverCoordinator &co, utl::network::default_buf<pkgBase>& buf, sock_id& sock)
						: m_oCoordinator(co), m_oSendBuf(buf), m_oUDPSock(sock), m_bIsRunning(true){};

				void		terminate(){ m_bIsRunning = false;}
				void		operator () ()
			{
				int buf_size = 1024;
				char *pBuf = (char *)malloc(buf_size);
				while(m_bIsRunning)
				{
					//1.等待缓冲区中有内容可以发送
					m_oCoordinator.PSendBuf();

					//2.确定套接字可以发送，若不可以发送，则等待
					if(!m_oCoordinator.getWritableFlag())
					{
						::WaitForSingleObject(m_oCoordinator.m_hWritableEvent);
						m_oCoordinator.setWritableFlag(true);
						::ResetEvent(m_oCoordinator.m_hWritableEvent);
					}
					//2.发送一个包
					m_oSendBuf.lock_queue();
					utl::network::pkgBase & pkt = m_oSendBuf.back();
					m_oSendBuf.pop();
					m_oSendBuf.unlock_queue();

					if(buf_size<pkt.size())
					{
						buf_size = pkt.size();
						pBuf = realloc(pBuf,buf_size);
					}
					int len = pkt.serialize(pBuf);
					::WSASend(m_oUDPSock,)
					
				}
			};

			protected:
				SenderRecverCoordinator &	m_oCoordinator;
				utl::network::default_buf<pkgBase> &	m_oSendBuf;
				sock_id &	m_oUDPSock;
				bool		m_bIsRunning;
		};//end class udp_sender
		class UDPRecver
		{

		};//end class udp_recver
	#else

	#endif
	};//end namespace network
};//end namespace utl;
#endif
