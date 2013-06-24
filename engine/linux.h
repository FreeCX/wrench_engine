// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Window
// Description:  Window system (linux)
//

#ifndef __KERNEL_WINDOW_LINUX__
#define __KERNEL_WINDOW_LINUX__

#include <stdarg.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>
#include "keymap.h"
#include "structures.h"
#include "memory.h"
#include "error.h"

typedef struct {
    Display                *display;
    GLXContext              context;
    Bool                    doubleBuffered;
    Window                  window;
    Window                  root;
    XSetWindowAttributes    setWindowAttr;
    XF86VidModeModeInfo     deskMode;
    XVisualInfo            *vInfo;
    XWindowAttributes       windowAttr;
    int                     screen;
    int                     fullscreen;
    int                     depth;
    int                     x;
    int                     y;
} we_window_t;

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
