// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Kernel
// Last update:  19/01/13
// Description:  Basic structure of the system
//

#ifndef __KERNEL_STRUCTURES__
#define __KERNEL_STRUCTURES__

enum {
	WE_FAILED = -1, 
	WE_SUCCESS = 1
};

typedef struct {
	int 		width;
	int 		height;
	int 		fullscreen;
	int 		debug;
	char 		*name;
} we_engine;

#endif