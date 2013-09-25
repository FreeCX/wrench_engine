// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Error
// Description:  Error handling system
//

#ifndef __KERNEL_ERROR__
#define __KERNEL_ERROR__

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

enum {
    WE_ERROR_NONE,
    WE_ERROR_ALLOC_MEMORY, 
    
    WE_ERROR_CLEAR_CONTEXT,
    WE_ERROR_DELETE_CONTEXT,
    WE_ERROR_REGISTER_WINDOW,
    WE_ERROR_CREATE_WINDOW,
    WE_ERROR_DC_CONTEXT,
    WE_ERROR_CHOOSE_PIXELFORMAT,
    WE_ERROR_SET_PIXELFORMAT,
    WE_ERROR_CREATE_CONTEXT,
    WE_ERROR_MAKE_CONTEXT,

    WE_ERROR_DRAW_CONTEXT,
    WE_ERROR_OPEN_DISPLAY,
    WE_ERROR_GLX_SUPPORT,
    WE_ERROR_GLX_VERSION,
    WE_ERROR_CHOOSE_VISUAL
};

/* export function */
void weSendError( const int error );
int weGetError( void );
char ** weGetErrorString( void );
void wePrintError( void );
void weModuleError( const char *fmt, ... );

#endif
