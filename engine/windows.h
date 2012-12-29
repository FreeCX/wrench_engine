// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Window
// Last update:  29/12/12
// Description:  Window system (windows)
//

#ifndef __KERNEL_WINDOW_WINDOWS__
#define __KERNEL_WINDOW_WINDOWS__

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "structures.h"

/* export function */

int WE_InitOpenGL(int mask);
int WE_CreateWindow(we_engine * engine);

int WE_Loop(void);
void WE_Kill(void);

void WE_SwapBuffers(void);

#endif
