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
#include "../../config_details/IniReader.h"
#include <cassert>

utl::IniReader::IniReader( const std::string &strIniFile )
: m_strIniFile(strIniFile)
{
}

utl::IniReader::~IniReader()
{
}

void utl::IniReader::addWantedProperty( const std::string & strConfigName, utl::ConfigValue::ConfigValueType_t t )
{
	m_oProperties.insert(std::make_pair(strConfigName,t));
}

void utl::IniReader::setConfig( const char *strConfigName, const char *strConfigVal )
{
	assert(strConfigName && strConfigVal && "null pointer");
	std::string tmpName(strConfigName);
	KeyValueTypes::iterator it = m_oProperties.find(tmpName);
	if(m_oProperties.end() == it)
	{
		assert(0 && "Not need this config!");
		return ;
	}
	assert(it->second == utl::ConfigValue::STRING_TYPE && "The config is not string_type!");
	utl::ConfigValue conf(utl::ConfigValue::STRING_TYPE, strConfigVal,strlen(strConfigVal));
	m_oValues.insert(std::make_pair(tmpName,conf));
}

void utl::IniReader::setConfig( const char *strConfigName, int iConfigVal )
{
	assert(strConfigName && "null pointer!");
	std::string tmpName(strConfigName);
	KeyValueTypes::iterator it = m_oProperties.find(tmpName);
	if(m_oProperties.end() == it)
	{
		assert(0 && "Not need this config!");
		return ;
	}
	assert(it->second == utl::ConfigValue::INT_TYPE && "The config is not int_type!");
	utl::ConfigValue conf(utl::ConfigValue::INT_TYPE, iConfigVal);
	m_oValues.insert(std::make_pair(tmpName,conf));
}


