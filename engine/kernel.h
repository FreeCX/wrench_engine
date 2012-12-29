// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Kernel
// Last update:  29/12/12
// Description:  The core of the system
//

#ifndef __WRENCH_KERNEL__
#define __WRENCH_KERNEL__

#ifdef __WIN32__
    #include "windows.h"
#elif __LINUX__
    #include "linux.h"
#endif

#include <stdio.h>

#include "memory.h"

/* export function */

int WE_Init(int argc, char **argv);
void WE_Info(void);
void WE_About(char **name, int *major_v, int *minor_v);

#endif
