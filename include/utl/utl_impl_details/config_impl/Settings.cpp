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
#include "../../config_details/Settings.h"
#include <iostream>
#include <stdio.h>
#include <cassert>


utl::Settings utl::Settings::sv_oInstance;

utl::Settings::Settings()
{
	utl::ConfigValue pNullConfig;
	m_oKeyVals.insert(std::make_pair("null-config",pNullConfig));
}

utl::Settings::~Settings()
{
}

utl::Settings & utl::Settings::getInstance()
{
	return sv_oInstance;
}

void utl::Settings::loadEnv( IniReader & oReader )
{
	FILE *fp = fopen(oReader.m_strIniFile.c_str(), "r");
	assert(fp && "Cannot open the file!");
	if(!fp)
		return ;

	char buf[1024];
	while(!feof(fp))
	{
		memset(buf,0,1024);
		fgets(buf,1024,fp);
		if(buf[0] == '#')
			continue;
		std::string tmp(buf);
		std::string::size_type pos1, pos2;


		pos1 = tmp.find_first_not_of("\t ");
		if(pos1 == tmp.npos)//该行为空行
			continue ;
		pos2 = tmp.find_first_of("\t =",pos1);
		if(pos2 == tmp.npos)	//该行只有一个字符串，异常
		{
			assert(0 && "Unknown config line!");
			continue;
		}

		std::string strKey = tmp.substr(pos1,pos2-pos1);

		pos1 = tmp.find_first_of('=',pos2);	//确认"="
		if(pos1 == tmp.npos)
		{
			assert(0 && "Cannot find = in this line!");
			continue;
		}
		pos1 = tmp.find_first_not_of("\t #\n",pos1+1);
		if(pos1 == tmp.npos)	//"="后什么都没有
		{
			assert(0 && "Cannot find value!");
			continue;
		}
		pos2 = tmp.find_first_of("\t #\n", pos1);

		std::string strValue = tmp.substr(pos1,pos2-pos1);

		addConfig(oReader, strKey,strValue);
	}
	fclose(fp);

	//将oReader中的key-value移动到settings中
	IniReader::KeyValues::iterator it;
	for(it = oReader.m_oValues.begin(); it!=oReader.m_oValues.end(); ++it)
	{
		m_oKeyVals.insert(std::make_pair(it->first,it->second));
	}
}


const utl::ConfigValue & utl::Settings::getConfigVal( std::string  strConfigName ) const
{
	IniReader::KeyValues::const_iterator it;
	it = m_oKeyVals.find(strConfigName);
	if(it == m_oKeyVals.end())
	{
		it = m_oKeyVals.find("null-config");
		return it->second;
	}
	return it->second;
}

void utl::Settings::addConfig(IniReader &oReader, const std::string &strConfigName, const std::string &strValue )
{
	ConfigValue::ConfigValueType_t t;
	utl::IniReader::KeyValueTypes::iterator it = oReader.m_oProperties.find(strConfigName);
	t = it->second;

	int iVal;
	utl::ConfigValue val;
	if(t == utl::ConfigValue::INT_TYPE)
	{
		iVal = atoi(strValue.c_str());
		val.m_value.intVal = iVal;
		val.m_valueType =utl:: ConfigValue::INT_TYPE;
	}
	else if(t == utl::ConfigValue::STRING_TYPE)
	{
		val.m_value.strVal = ConfigValue::MultiCharType(strValue.c_str(),strValue.length());
		val.m_valueType = utl::ConfigValue::STRING_TYPE;
	}

	m_oKeyVals.insert(std::make_pair(strConfigName,val));
}


