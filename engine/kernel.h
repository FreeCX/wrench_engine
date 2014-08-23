// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Kernel
// Description:  The core of the system
//

#ifndef __WRENCH_KERNEL__
#define __WRENCH_KERNEL__

#ifdef __WIN32__
    #include "windows.h"
#elif __linux__
    #include <sys/utsname.h>
    #include <execinfo.h>
    #include "linux.h"
#endif

#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "error.h"
#include "input.h"
#include "memory.h"
#include "structures.h"

/* export function */
int weInit( const int argc, char **argv );
void weInfo( void );
void weAbout( char **name, int *major_v, int *minor_v );
uint32 weTicks( void );
float weGetFps( void );
void weTimerInit( void );
void weTimerLoop( void );
void weTimerSet( uint32 usec, void (*f)( void ) );
void weTimerKill( void );

#endif
