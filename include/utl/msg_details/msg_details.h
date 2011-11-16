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

#ifndef __UTILS_MSG_SWITCH_H
#define __UTILS_MSG_SWITCH_H

#include "../mutex_details/mutex.h"
#include "../SmartPtrs.h"
#include "../utl_config.h"
#include <vector>
#include <map>
#include "../OsUtils.h"

#define INVALID_MSG_TYPE  0

namespace utl
{
	//forward declaration
	template < class MsgType, class thrd_attr> class MsgPortBase;	
	template < class MsgType, class thrd_attr> class MsgPort;

	//class MsgSwitch////////////////////////////////////////////////////////////////////////
	template<class MsgType, class thrd_attr = utl::multi_thrd>
	class MsgSwitch
	{
		protected:
			typedef   typename thrd_attr::template queue<MsgType *>		queue;
			typedef   typename utl::MsgPortBase<MsgType, thrd_attr>		msg_port_type;
			typedef   std::vector<msg_port_type *>						                ports_container;
			typedef   std::map<int, ports_container *>					            type_to_ports;
			typedef   typename thrd_attr::Mutex							                Mutex;

		protected:
			MsgSwitch( ) : m_oMutex( ),  m_oPorts( ),  m_iPortsNum(0){ };
			MsgSwitch(const MsgSwitch<MsgType,  thrd_attr> & ms){ };
			MsgSwitch<MsgType, thrd_attr> &	operator = (const MsgSwitch<MsgType,  thrd_attr> & ms){ };

		public:
			static  MsgSwitch<MsgType, thrd_attr>&   getInstance( )
			{
				return pInstance;
			 }
			int	getPortsNum( )   const
			{
				m_oMutex.lock( ); 
				int i = m_iPortsNum; 
				m_oMutex.unlock( ); 
				return i;
			}
			int	getTypesNum( )  const
			{
				m_oMutex.lock( );
				int i = static_cast<int>( m_oPorts.size() ); 
				m_oMutex.unlock;
				return i;
			}

		protected:
			static int	initInstance( )
			{
				pInstance = new MsgSwitch<MsgType, thrd_attr>;
				//Fix it: throw exception or not?
				assert( pInstance && "bad alloc!" );
				return 1;
			};
			friend class MsgPortBase<MsgType, thrd_attr>;

			void	 sendMsg(int iMsgType, const utl::SharedPtr<MsgType, thrd_attr> & pMsg)
			{
				typename thrd_attr::Guard temp_guard( m_oMutex );
				typename type_to_ports::const_iterator it = m_oPorts.find( iMsgType );
				if( it == m_oPorts.end( ) )
				{
					assert(0 && "unexpected msg type!");
					return ;
				}
				ports_container *pPorts = it->second;
				if( pPorts == 0 )
				{
					assert(0 && "unexpected msg type or no msg port to recv this msg type!");	
				}
				for( typename ports_container::size_type i = 0;  i<pPorts->size( );  ++i )
				{
					pPorts->at(i)->addMsg( iMsgType,  pMsg );
				}
			};
			void	 regInterestTypes(MsgPortBase<MsgType,thrd_attr> * const port,const std::vector<int> &msg_types)
			{
				typename  thrd_attr::Guard temp_guard( m_oMutex );
				typename  type_to_ports::iterator  it;
				ports_container *pPorts = 0;
				for(std::vector<int>::size_type i = 0;  i<msg_types.size( );  ++i)
				{
					it  =  m_oPorts.find( msg_types[i] );
					if(m_oPorts.end( ) == it)
					{
						pPorts = new ports_container( );
						std::pair<typename type_to_ports::iterator, bool> res = m_oPorts.insert(std::make_pair(msg_types[i],pPorts));
						if( !res.second )
						{
							assert(0 && "insert error but cannot find it, unknown error!");
							return ;
						}
					}
					else
					{
						pPorts = it->second;
					}
					assert(pPorts && "cannot dereference null pointer");
					//make sure there is only one unique msg port!
					int j;
					for(j = 0;  pPorts && j<static_cast<int>(pPorts->size( ) ); ++j)
					{
						if(pPorts && pPorts->at(j) == port)
						break;
					}
					if( pPorts && j>= static_cast<int>(pPorts->size() ) )
					{
						pPorts->push_back( port );
					}
			}
		m_iPortsNum ++;
	};

	private:
		type_to_ports					m_oPorts;
		mutable Mutex				m_oMutex;
		int							     	m_iPortsNum;

		static MsgSwitch<MsgType, thrd_attr>			pInstance;
};//end class MsgSwitch

	template <class MsgType, class thrd_attr>
	MsgSwitch<MsgType, thrd_attr> MsgSwitch<MsgType, thrd_attr>::pInstance ;
	
	//class MsgPortBase ////////////////////////////////////////////////////////////////////////
	template <class MsgType, class thrd_attr> 
	class MsgPortBase
	{
		protected:
			typedef std::pair<int, utl::SharedPtr<MsgType, thrd_attr> >		element;
			typedef typename thrd_attr::template queue<element>			queue;

			MsgSwitch<MsgType, thrd_attr> *		m_pMsgSwitch;
			queue		m_oMsgQueue;
			std::vector<int>		m_oInterestTypes;

		protected:
			MsgPortBase(): m_pMsgSwitch(0), m_oMsgQueue( )
			{
				m_pMsgSwitch = & MsgSwitch<MsgType, thrd_attr>::getInstance();
			};

		public:
			virtual ~MsgPortBase(){};

			//注册本消息端口需要接收的消息类型
			void	  regInterestTypes(const std::vector<int> &	oTypes)
			{
				m_oInterestTypes = oTypes;
				return m_pMsgSwitch->regInterestTypes(this,oTypes);
			}; 

			//获得本消息接口需要接收的消息类型
			const std::vector<int>	&		interestTypes() const
			{
				return m_oInterestTypes;
			};
			//发出消息
			void	 sendMsg(int iMsgType, const utl::SharedPtr<MsgType, thrd_attr> & pMsg)
			{
				m_pMsgSwitch->sendMsg(iMsgType,pMsg);
			};
			//将消息放到本队列中
			void	 pushBackMsg(int iMsgType,const utl::SharedPtr<MsgType, thrd_attr> & pMsg)
			{
				addMsg(iMsgType,pMsg);
			};

			//得到消息队列的长度
			int	msgQueueSize()
			{
				m_oMsgQueue.lockQueue();
				int i = static_cast<int>(m_oMsgQueue.size());
				m_oMsgQueue.unlockQueue();
				return i;
			};

			//获得消息
			virtual int		getMsg(utl::SharedPtr<MsgType, thrd_attr> & pMsg) = 0;

		protected:
			friend class MsgSwitch<MsgType, thrd_attr>;

			virtual void	 addMsg(int iMsgType, const utl::SharedPtr<MsgType, thrd_attr> & pMsg) = 0;
	};//end class MsgPortBase;

	//class MsgPort////////////////////////////////////////////////////////////////////////
	template <class MsgType, class thrd_attr>
	class MsgPort : public MsgPortBase<MsgType, thrd_attr>
	{
		private:
			MsgPort(){};
		public:
			virtual ~MsgPort(){};
	};//end class MsgPort;

	//class MsgPort 偏特化////////////////////////////////////////////////////////////////////////
	template <class MsgType>
	class MsgPort<MsgType, utl::single_thrd>: public MsgPortBase<MsgType, utl::single_thrd>
	{
		public:
			MsgPort(): MsgPortBase<MsgType, utl::single_thrd>(){};
			virtual ~MsgPort(){};

			//获得消息
			virtual int	  getMsg(utl::SharedPtr<MsgType, utl::single_thrd> & pMsg)
			{
				if(m_oMsgQueue.empty())
				{
					return INVALID_MSG_TYPE;
				}
				typename MsgPortBase<MsgType, utl::single_thrd>::element & e = m_oMsgQueue.front( );
				m_oMsgQueue.pop();

				pMsg = e.second;
				return e.first;
			};

		protected:
			friend class MsgSwitch<MsgType, utl::single_thrd>;
			virtual void	 addMsg(int iMsgType, const utl::SharedPtr<MsgType, utl::single_thrd> & pMsg)
			{
				typename MsgPortBase<MsgType, utl::single_thrd>::element e = std::make_pair<int, utl::SharedPtr<MsgType, utl::single_thrd> >(iMsgType,pMsg);
				m_oMsgQueue.push(e);
			};
		protected:
			using MsgPortBase<MsgType, utl::single_thrd>::m_oMsgQueue;
		};//end class MsgPort 偏特化

	//class MsgPort偏特化////////////////////////////////////////////////////////////////////////
	template <class MsgType>
	class MsgPort<MsgType, utl::multi_thrd> : public MsgPortBase<MsgType, utl::multi_thrd>
	{
		public:
			MsgPort(): MsgPortBase<MsgType, utl::multi_thrd>()
			{
				MsgPortBase<MsgType, utl::multi_thrd>::m_pMsgSwitch = & MsgSwitch<MsgType, utl::multi_thrd>::getInstance();
			};
			virtual ~MsgPort(){};
			
			//获得消息
			int	getMsg(utl::SharedPtr<MsgType, utl::multi_thrd> & pMsg)
			{
				m_oSemaphore.P();
				m_oMsgQueue.lockQueue();
				
				typename MsgPortBase<MsgType, utl::multi_thrd>::element & e = m_oMsgQueue.front();
				pMsg = e.second;
				m_oMsgQueue.pop();
				m_oMsgQueue.unlockQueue();
				
				return e.first;
			};

		protected:
			friend class MsgSwitch<MsgType, utl::multi_thrd>;
			void	 addMsg(int iMsgType, const utl::SharedPtr<MsgType, utl::multi_thrd> & pMsg)
			{
				typename MsgPortBase<MsgType, utl::multi_thrd>::element e = std::make_pair<int, utl::SharedPtr<MsgType, utl::multi_thrd> >(iMsgType,pMsg);
				m_oMsgQueue.lockQueue();
				m_oMsgQueue.push(e);
				m_oMsgQueue.unlockQueue();
				m_oSemaphore.V();
			};
		protected:
			utl::Semaphore	m_oSemaphore;
			using MsgPortBase<MsgType, utl::multi_thrd>::m_oMsgQueue;
		};//end class MsgPort

}//end namespace utl;
#endif

