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

#ifndef __UTILS_CONFIG_DETAILS_CONFIG_VALUE_H
#define __UTILS_CONFIG_DETAILS_CONFIG_VALUE_H
#include "../MultiChar.h"

namespace utl{

	class ConfigValue{
	public:
		typedef enum{
			NULL_TYPE = 1,
			INT_TYPE = 2,
			STRING_TYPE = 3
		}ConfigValueType_t;

		typedef utl::MultiChar<32>	MultiCharType;
		struct ConfigValue_t{
			int						intVal;
			MultiCharType			strVal;
			ConfigValue_t();
			ConfigValue_t(int iVal);
			ConfigValue_t(const char *strValue, int iStrLen);
		};

		ConfigValue();
		ConfigValue(ConfigValueType_t t,const char * strValue, int iStrLen);
		ConfigValue(ConfigValueType_t t, int iValue);
		ConfigValue(const ConfigValue & confValue);
		~ConfigValue();

	public:
		ConfigValueType_t			m_valueType;
		ConfigValue_t				m_value;
	};//end class ConfigValue

};//end namespace utl

#endif

