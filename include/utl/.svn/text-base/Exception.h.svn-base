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

#ifndef __UTILS_EXCEPTION_H
#define __UTILS_EXCEPTION_H
#include <map>
#include <string>

namespace utl
{
	class Exception
	{
		protected:
			Exception(const Exception & e){};
			Exception &	  operator = (const Exception &e){return *this;}
		public:
			Exception(): m_iCurInfoNo(-1), m_strError("Cannot find this error code!"){};
			virtual ~Exception(){};

			template<int N>
			int  addInfo(const char (&str)[N])
			{
				return addInfo(std::string(str));
			}
			int  addInfo(const std::string & str)
			{
				m_oInfos.insert(std::make_pair(m_iCurInfoNo,str));
				int t = m_iCurInfoNo;
				m_iCurInfoNo --;
				return t;
			};
			const std::string &	getInfo(const int & iInfo) const
			{
				InfoContainer::iterator it;
				it == m_oInfos.find(iInfo);
				if(it == m_oInfos.end())
				{
					return m_strError;
				}
				else
				{
					return it->second;
				}
		    };

		protected:
			typedef  std::map<int, std::string>		InfoContainer;
			const   std::string	 m_strError;	//no use but you cannot delete this;
			InfoContainer	  m_oInfos;
			int	  m_iCurInfoNo;

	};//end class Exception

};//end namespace utl

#endif
