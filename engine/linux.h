// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Window
// Last update:  29/12/12
// Description:  Window system (linux)
//

#ifndef __KERNEL_WINDOW_LINUX__
#define __KERNEL_WINDOW_LINUX__

#include <GL/gl.h>
#include <GL/glu.h>

#include "structures.h"

/* export function */

int weInitOpenGL( const int mask );
int weCreateWindow( we_engine * engine );

int weLoop( void );
void weKill( void );

void weSwapBuffers( void );

#endif
