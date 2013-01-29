// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Window
// Last update:  29/01/13
// Description:  Window system (linux)
//

#include "linux.h"

static we_window_t wgl;

int weInitOpenGL( const int mask )
{
    /* insert code */
}

int weCreateWindow( we_engine * engine )
{
    /* insert code */
}

int weLoop( void )
{
    /* insert code */
}

void weKill( void )
{
    if ( wgl.context ) {
        if ( !glXMakeCurrent( wgl.display, wgl.window, wgl.context ) ) {
			weSendError( WE_ERROR_DRAW_CONTEXT );
			glXDestroyContext( wgl.display, wgl.context );
			wgl.context = WE_NULL;
		}
    }
    if ( wgl.fullscreen ) {
        XF86VidModeSwitchToMode( wgl.display, wgl.screen, &wgl.deskMode );
        XF86VidModeSetViewPort( wgl.display, wgl.screen, 0, 0 );
    }
    XCloseDisplay( wgl.display );
}

void weSwapBuffers( void )
{
    glXSwapBuffers( wgl.display, wgl.window );
}

