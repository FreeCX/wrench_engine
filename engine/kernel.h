// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Kernel
// Last update:  19/01/13
// Description:  The core of the system
//

#ifndef __WRENCH_KERNEL__
#define __WRENCH_KERNEL__

#ifdef __WIN32__
    #include "windows.h"
#elif __linux__
	#include <sys/utsname.h>
    #include "linux.h"
#endif

#include <stdio.h>
#include <getopt.h>

#include "error.h"
#include "input.h"
#include "memory.h"

/* export function */

int weInit( const int argc, char **argv );
void weInfo( void );
void weAbout( char **name, int *major_v, int *minor_v );

#endif
