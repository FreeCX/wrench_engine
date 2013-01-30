// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Window
// Last update:  30/01/13
// Description:  Window system (linux)
//

#ifndef __KERNEL_WINDOW_LINUX__
#define __KERNEL_WINDOW_LINUX__

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>

#include "structures.h"
#include "error.h"

typedef struct {
	Display 				*display;
    GLXContext 				context;
    Bool 					doubleBuffered;
    Window 					window;
    Window 					root;
    XSetWindowAttributes 	setWindowAttr;
    XF86VidModeModeInfo 	deskMode;
    XVisualInfo 			*vInfo;
    XWindowAttributes 		windowAttr;
    int 					screen;
    int 					fullscreen;
    int 					depth;
    int 					x;
    int 					y;
} we_window_t;

/* export function */
int weInitOpenGL( const int glFlag );
int weCreateWindow( we_engine_t * engine );
int weLoop( void );
void weKill( void );
void weSwapBuffers( void );

#endif
