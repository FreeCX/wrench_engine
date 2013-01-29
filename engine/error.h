// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Error
// Last update:  19/01/13
// Description:  Error handling system
//

#ifndef __KERNEL_ERROR__
#define __KERNEL_ERROR__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    WE_ERROR_NONE,
    WE_ERROR_ALLOC_MEMORY, 
    WE_ERROR_CLEAR_CONTEXT,
    WE_ERROR_DELETE_CONTEXT,
    WE_ERROR_REGISTER_WINDOW,

    WE_ERROR_DRAW_CONTEXT
};

/* export function */

void weSendError( const int error );
int weGetError( void );
char ** weGetErrorString( void );
void wePrintError( void );

#endif
