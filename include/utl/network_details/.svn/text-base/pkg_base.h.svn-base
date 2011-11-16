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

#ifndef __UTILS_NETWORK_DETAILS_PKG_BASE_H
#define __UTILS_NETWORK_DETAILS_PKG_BASE_H
namespace utl
{
	namespace network
	{
		class pkgBase
		{
			public:
				pkgBase(): m_uiPkgLen(0), m_pContent(0){};
				pkgBase(unsigned int uiPkgLen, void *pContent): m_uiPkgLen(uiPkgLen), m_pContent(pContent){};
				pkgBase(const pkgBase & pkg): m_uiPkgLen(pkg.m_uiPkgLen), m_pContent(pkg.m_pContent){};
				virtual ~pkgBase(){};

				unsigned int	size() const{return m_uiPkgLen;};
				void *				get()	const{return m_pContent;};

				virtual int			serialize(void *buf);
				virtual int			deserialize(void *buf);
			
			protected:
				unsigned int	m_uiPkgLen;
				void *				m_pContent;
		};//end class pkgBase
	};//end namespace network
};	//end namespace utl
#endif

