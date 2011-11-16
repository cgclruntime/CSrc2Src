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
#ifndef __UTILS_MULTI_CHAR_H
#define __UTILS_MULTI_CHAR_H
#include <cassert>
#include <string>
namespace utl{


template <int N=16>
class MultiChar{
public:
	MultiChar()
		: m_bIsAllocChar(false)
	{
	};
	explicit MultiChar(int iSize)
	{
		if(iSize >N)
		{
			m_bIsAllocChar = true;
			m_oChars.m_oDetails.m_pChars = (char *)malloc(iSize + N);
			assert( m_oChars.m_oDetails.m_pChars && "Alloc error!");
			m_oChars.m_oDetails.m_iSize = iSize + N;
		}
		else
		{
			m_bIsAllocChar = false;
		}
	}
	MultiChar(const char * str, int iStrLen)
	{
		if(iStrLen >N)
		{
			m_bIsAllocChar = true;
			m_oChars.m_oDetails.m_pChars = (char *)malloc(iStrLen + N);
			assert( m_oChars.m_oDetails.m_pChars && "Alloc error!");
			m_oChars.m_oDetails.m_iSize = iStrLen + N;
			memcpy(m_oChars.m_oDetails.m_pChars, str, iStrLen);
		}
		else
		{
			m_bIsAllocChar = false;
			memcpy(m_oChars.m_acChars, str, iStrLen);
		}
	};
	template <int M>
	MultiChar(char str[M])
	{
		if(M >N)
		{
			m_bIsAllocChar = true;
			m_oChars.m_oDetails.m_pChars = (char *)malloc(M);
			assert( m_oChars.m_oDetails.m_pChars && "Alloc error!");
			m_oChars.m_oDetails.m_iSize = M;
			memcpy(m_oChars.m_oDetails.m_pChars, str, M);
		}
		else
		{
			m_bIsAllocChar = false;
			memcpy(m_oChars.m_acChars, str, M);
		}
	};

	MultiChar(const MultiChar<N> & oChars)
	{
		if(&oChars == this)
			return ;
		if(oChars.m_bIsAllocChar)
		{
			m_bIsAllocChar = oChars.m_bIsAllocChar;
			m_oChars.m_oDetails.m_iSize = oChars.m_oChars.m_oDetails.m_iSize;
			m_oChars.m_oDetails.m_pChars = (char *) malloc(m_oChars.m_oDetails.m_iSize);
			memcpy(m_oChars.m_oDetails.m_pChars, oChars.m_oChars.m_oDetails.m_pChars, m_oChars.m_oDetails.m_iSize);
		}
		else{
			m_bIsAllocChar = false;
			memcpy(m_oChars.m_acChars, oChars.m_oChars.m_acChars, N);
		}
	};

	MultiChar &					operator = (const MultiChar<N> & oChars)
	{
		if(&oChars == this)
			return *this;
		if(m_bIsAllocChar)
			delete m_oChars.m_oDetails.m_pChars;
		if(oChars.m_bIsAllocChar)
		{
			m_bIsAllocChar = oChars.m_bIsAllocChar;
			m_oChars.m_oDetails.m_iSize = oChars.m_oChars.m_oDetails.m_iSize;
			m_oChars.m_oDetails.m_pChars = (char *) malloc(m_oChars.m_oDetails.m_iSize);
			memcpy(m_oChars.m_oDetails.m_pChars, oChars.m_oChars.m_oDetails.m_pChars, m_oChars.m_oDetails.m_iSize);
		}
		else{
			m_bIsAllocChar = false;
			memcpy(m_oChars.m_acChars, oChars.m_oChars.m_acChars, N);
		}
		return *this;
	}
	virtual ~MultiChar()
	{
		if(m_bIsAllocChar)
			delete m_oChars.m_oDetails.m_pChars;
	};

	char &			operator[](unsigned int i){
		if(m_bIsAllocChar)
		{
			assert(i<m_bIsAllocChar && "Index overflow!");
			return m_oChars.m_oDetails.m_pChars[i];
		}
		else
		{
			assert(i<N && "Index overflow!");
			return m_oChars.m_acChars[i];
		}
	}

	char *			get() const {
		if(m_bIsAllocChar)
		{
			return m_oChars.m_oDetails.m_pChars;
		}
		else
			return m_oChars.m_acChars;
	};
	int				size() const
	{
		if(m_bIsAllocChar)
			return m_oChars.m_oDetails.m_iSize;
		else
			return N;
	};

	int				strlen() const
	{
		if(m_bIsAllocChar)
			return ::strlen(m_oChars.m_oDetails.m_pChars);
		else
			return ::strlen(m_oChars.m_acChars);
	};
protected:
	typedef struct {
		int		m_iSize;
		char *	m_pChars;
	}AllocMultiCharType;

	typedef union{
		char					m_acChars[N];
		AllocMultiCharType		m_oDetails;
	}MultiCharType;

	bool						m_bIsAllocChar;
	mutable MultiCharType				m_oChars;
};//end class StrContainer;

};//end namespace utl;

#endif
