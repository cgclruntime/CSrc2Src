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

#ifndef __UTILS_CONFIG_H
#define __UTILS_CONFIG_H

#include "config_details/Settings.h"


#define NEW_INI_READER(name) \
	class name : public utl::IniReader { \
	public:	\
	name(std::string iniFile):utl::IniReader(iniFile){addProperties();};	\
	virtual ~name(){}; \
	void				addProperties(); \
	};	
	
#define  BEGIN_INI_READER(name) \
	void name::addProperties() {
#define END_INI_READER }

#define  ADD_WANTED_PROPERTY(config, value_t) \
	addWantedProperty(config, value_t);


/*example
//.h 
NEW_INI_READER(PublicConfig, "public.ini")

//.cpp
BEGIN_INI_READER(PublicConfig)
ADD_WANTED_PROPERTY("server-ip",ConfigValue::STRING_TYPE)
ADD_WANTED_PROPERTY("connect-time", ConfigValue::INT_TYPE)
END_INI_READER


*/
#endif

