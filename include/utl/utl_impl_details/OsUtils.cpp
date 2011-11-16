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
#include "../OsUtils.h"


#if defined WIN32 || defined _WIN32
#include <windows.h>


void	utl::sleep(unsigned int milliseconds)
{
	Sleep(milliseconds);
};

#else
#include <unistd.h>

void	 utl::sleep(unsigned int milliseconds)
{
	usleep(milliseconds);
};
#endif