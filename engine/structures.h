// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Kernel
// Last update:  29/12/12
// Description:  Basic structure of the system
//

#ifndef __KERNEL_STRUCTURES__
#define __KERNEL_STRUCTURES__

#define WE_FAILED			-1
#define WE_SUCCESS			 1

#ifdef __WIN32__
    typedef unsigned __int64 uint;
#endif

typedef struct {
	char *name;
	int width;
	int height;
	int fullscreen;
	int debug;
} we_engine;

#endif