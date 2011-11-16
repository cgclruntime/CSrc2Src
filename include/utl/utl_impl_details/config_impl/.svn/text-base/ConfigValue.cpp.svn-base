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
#include "../../config_details/ConfigValue.h"

utl::ConfigValue::ConfigValue()
: m_valueType(ConfigValue::NULL_TYPE)
{
}

utl::ConfigValue::ConfigValue( ConfigValueType_t t,const char * strValue , int iStrLen)
: m_valueType(t)
, m_value(strValue,iStrLen)
{
	assert(strValue && iStrLen>0);
	assert(t == ConfigValue::STRING_TYPE);
}

utl::ConfigValue::ConfigValue( ConfigValueType_t t, int iValue )
: m_valueType(t)
, m_value(iValue)
{
	assert(t == ConfigValue::INT_TYPE);
}

utl::ConfigValue::ConfigValue( const ConfigValue & confValue )
{
	if(&confValue == this)
		return ;
	m_valueType = confValue.m_valueType;
	if(m_valueType == ConfigValue::INT_TYPE)
		m_value.intVal = confValue.m_value.intVal;
	else if(m_valueType == ConfigValue::STRING_TYPE)
		m_value.strVal = confValue.m_value.strVal;
}

utl::ConfigValue::~ConfigValue()
{
}

utl::ConfigValue::ConfigValue_t::ConfigValue_t( int iVal )
	: intVal(iVal)
{
}

utl::ConfigValue::ConfigValue_t::ConfigValue_t( const char *strValue, int iStrLen )
	:strVal(strValue,iStrLen)
{
}

utl::ConfigValue::ConfigValue_t::ConfigValue_t()
	: intVal(0)
	, strVal()
{
}


