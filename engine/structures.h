// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Kernel
// Last update:  30/01/13
// Description:  Basic structure of the system
//

#ifndef __KERNEL_STRUCTURES__
#define __KERNEL_STRUCTURES__

enum {
	WE_FAILURE 	= -1, 
	WE_NULL 	= 0,
	WE_SUCCESS 	= 1
};

enum {
	WE_GL_DOUBLEBUFFER
};

typedef struct {
	int 		width;
	int 		height;
	int 		fullscreen;
	int 		debug;
	char 		*name;
} we_engine_t;

#endif