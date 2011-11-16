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

#ifndef __UTILS_CONFIG_DETAILS_INI_READER_H
#define __UTILS_CONFIG_DETAILS_INI_READER_H
#include <map>
#include "ConfigValue.h"

namespace utl
{
	class IniReader{
	public:
		typedef std::map<std::string, utl::ConfigValue>							KeyValues;
		typedef std::map<std::string, utl::ConfigValue::ConfigValueType_t>		KeyValueTypes;
	protected:
		IniReader(const std::string &strIniFile);
	public:
		virtual ~IniReader();

		virtual void							addWantedProperty(const std::string & strConfigName, utl::ConfigValue::ConfigValueType_t t);


		virtual void							setConfig(const char *strConfigName, const char *strConfigVal);

		virtual void							setConfig(const char *strConfigName, int iConfigVal);

	protected:
		friend class Settings;

		
	protected:
		std::string						m_strIniFile;
		KeyValues						m_oValues;
		KeyValueTypes					m_oProperties;
	};//end class IniReader
};//end namespace utl

#endif

