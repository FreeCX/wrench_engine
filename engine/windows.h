// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Window
// Last update:  29/01/13
// Description:  Window system (windows)
//

#ifndef __KERNEL_WINDOW_WINDOWS__
#define __KERNEL_WINDOW_WINDOWS__

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "structures.h"
#include "error.h"

/* export function */

int weInitOpenGL( const int mask );
int weCreateWindow( we_engine * engine );

int weLoop( void );
void weKill( void );

void weSwapBuffers( void );

#endif
