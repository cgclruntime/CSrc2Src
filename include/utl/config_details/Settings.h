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

#ifndef __UTILS_CONFIG_DETAILS_SETTINGS_H
#define __UTILS_CONFIG_DETAILS_SETTINGS_H
#include "IniReader.h"

namespace utl
{
	class Settings{
	protected:
		Settings();
	public:
		virtual ~Settings();

		static Settings &					getInstance();

		virtual void						loadEnv(IniReader & oReader);

		virtual const ConfigValue &			getConfigVal(std::string  strConfigName) const;

	protected:
		virtual void							addConfig(IniReader &oReader,const std::string &strConfigName, const std::string &strValue);
	protected:
		static Settings						sv_oInstance;
		utl::IniReader::KeyValues			m_oKeyVals;
	};//end class Settings
};//end namespace utl
#endif

