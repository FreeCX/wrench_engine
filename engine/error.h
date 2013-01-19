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
    WE_ERROR_ALLOC_MEMORY
};

/* export function */

void weSendError( const int error );
int weGetError( void );
char ** weGetErrorString( void );
void wePrintError( void );

#endif
