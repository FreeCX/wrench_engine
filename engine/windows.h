// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Window
// Description:  Window system (windows)
//

#ifndef __KERNEL_WINDOW_WINDOWS__
#define __KERNEL_WINDOW_WINDOWS__

#include <stdarg.h>
#include <windows.h>
#include <winuser.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "keymap.h"
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
void weGetCursorPos( int *x, int *y );
void weRedraw( void );
void weRenderFunc( void ( *param )( void ) );
void weResizeFunc( void ( *param )( int, int ) );
void weMouseActionFunc( void ( *param )( int, int, int, int ));
void weMouseMotionFunc( void ( *param )( int, int ));
void weKeyboardFunc( void ( *param )( unsigned int * ));

#endif
