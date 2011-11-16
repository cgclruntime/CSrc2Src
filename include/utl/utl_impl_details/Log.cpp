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
#include "../Log.h"

#ifdef LOG_4_CPLUS


void	utl::startLogInfrastrue(const char *path, int log_level){

	/* step 1: Instantiate an appender object */
	//log4cplus::SharedAppenderPtr _append(new log4cplus::RollingFileAppender( logfilename.c_str(), 20*1024, 1000));
	log4cplus::SharedAppenderPtr _append(new log4cplus::FileAppender( path));//, 20*1024, 1000));
	//SharedAppenderPtr _append(new DailyRollingFileAppender(logfilename.c_str(), HOURLY, true, 1000));
	_append->setName("append for test");

	/* step 2: Instantiate a layout object */
	std::string pattern = "%-6p  %-15c %D %m %n ";

	std::auto_ptr<log4cplus::Layout>  _layout(new log4cplus::PatternLayout(pattern));

	/* step 3: Attach the layout object to the appender */
	_append->setLayout( _layout );

	/* step 4: Instantiate a logger object */
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();

	_logger.setLogLevel( log_level);

	/* step 5: Attach the appender object to the logger  */
	_logger.addAppender(_append);
}
#else

void	utl::startLogInfrastrue(const char *path, int log_level)
{
}
#endif

