// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Window
// Last update:  28/02/13
// Description:  Window system (windows)
//

#ifndef __KERNEL_WINDOW_WINDOWS__
#define __KERNEL_WINDOW_WINDOWS__

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "structures.h"
#include "error.h"
#include "memory.h"

/* export function */
int weInitWindow( const int width, const int height, const int flag );
int weInitOpenGL( const int glFlag );
int weCreateWindow( const char *title );
int weLoop( void );
void weKill( void );
void weSwapBuffers( void );
void weSetCaption( const char *fmt, ... );
void weRenderFunc( void ( *param )( void ) );
void weResizeFunc( void ( *param )( int, int ) );

#endif
