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

int WE_InitOpenGL(int mask);
int WE_CreateWindow(we_engine * engine);

int WE_Loop(void);
void WE_Kill(void);

void WE_SwapBuffers(void);

#endif
