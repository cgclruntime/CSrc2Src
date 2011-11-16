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

#ifndef __UTILS_STATE_H
#define __UTILS_STATE_H
#include "Exception.h"
#include <vector>

#define __INITIAL_STATE__ 0
namespace utl
{
		template<class _Tx>
		class State
		{
			public:
				typedef _Tx		InputType;
				typedef utl::Exception		ExceptionType;

				typedef void	(*callBack)(int srcState, const InputType & input, int dstState, bool isDstStateFinal);

			public:
				State(int inital = __INITIAL_STATE__): m_iCurState(inital)
				{
					EdgesContainer e;
					std::pair<StatesContainer::iterator, bool> res = m_oStates.insert(std::make_pair(inital, e));
					m_pCurState2Edges = & (res.first->second);
				};
				virtual ~State(){};
				int	transform(int srcState, const InputType &input, int dstState, callBack pCall = 0, bool isFinalState = false)
				{
					StatesContainer::iterator it = m_oStates.find(srcState);
					EdgeToState e;
					e.m_bDstStateIsFinal = isFinalState;
					e.m_iDstState = dstState;
					e.m_oInput = input;
					e.m_pCall = pCall;
					EdgesContainer *pEdges =0;

					//insert this transformation
					if(it == m_oStates.end())
					{
						EdgesContainer es;
						std::pair<StatesContainer::iterator, bool> res = m_oStates.insert(std::make_pair(srcState, es));
						pEdges = & (res.first->second);
					}
					else
					{
						pEdges = &(it->second);
					}

					EdgesContainer::iterator it_edges;
					for(it_edges = pEdges->begin(); it_edges != pEdges->end(); ++it_edges)
					{
						if(it_edges->m_iDstState == dstState)
						{
							if(it_edges->m_oInput != input)
							{
								return m_oExcepts.addInfo("Transform to two same destination states, this is forbidden!");
							}
							else
							{
								return dstState;
							}
						}
						if(it_edges->m_oInput == input)
						{
							return m_oExcepts.addInfo("Transform with the same input!");
						}
					}
					pEdges->push_back(e);

					//insert the destination state
					if(m_oStates.find(dstState) == m_oStates.end())
					{
						EdgesContainer es;
						std::pair<StatesContainer::iterator, bool> res = m_oStates.insert(std::make_pair(dstState, es));
					}
					return dstState;
				};

				int   go(const InputType & e)
				{
					if(m_pCurState2Edges == 0)
					{
						return m_oExcepts.addInfo("Unexpected error!");
					}
					EdgesContainer::iterator it;
					for(it = m_pCurState2Edges->begin(); it!=m_pCurState2Edges->end(); ++it)
					{
						if(it->m_oInput == e)
						{
							(*(it->m_pCall))(m_iCurState, e, it->m_iDstState,it->m_bDstStateIsFinal);
							if(it->m_bDstStateIsFinal)
							{
								m_iCurState = m_iStartState;
							}
							else
							{
								m_iCurState = it->m_iDstState;
							}
							StatesContainer::iterator it_states = m_oStates.find(m_iCurState);
							if(it_states == m_oStates.end())	
							{
								return m_oExcepts.addInfo("Cannot find the destination state!");
							}
							m_pCurState2Edges = &(it_states->second);
							return m_iCurState;
						}
					}
					if(it == m_pCurState2Edges->end())
					{
						return m_oExcepts.addInfo("No transformation with this current state!");
					}
					return m_iCurState;
				};

				int	curState() const{return m_iCurState;};
		protected:
			struct EdgeToState 
			{
				InputType				m_oInput;
				int						m_iDstState;
				callBack 				m_pCall;
				bool					m_bDstStateIsFinal;
			};
			typedef std::vector<EdgeToState >		EdgesContainer;
			typedef std::map<int, EdgesContainer >	 StatesContainer;

			ExceptionType		m_oExcepts;

			int	m_iStartState;
			StatesContainer		m_oStates;
			int	m_iCurState;
			EdgesContainer *	m_pCurState2Edges;
		};//end class State

};//end namespace utl;
#endif


