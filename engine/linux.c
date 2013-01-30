// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Window
// Last update:  30/01/13
// Description:  Window system (linux)
//

#include "linux.h"

static we_window_t wgl;

int weInitOpenGL( const int glFlag )
{
    return WE_NULL;
}

int weCreateWindow( we_engine_t * engine )
{
    static int counter = 0;
    XF86VidModeModeInfo **modes;
    int glx_major, glx_minor;
    int vme_major, vme_minor;
    int modeNum, bestMode, i;
    char *env = getenv("DISPLAY");

    if ( !( wgl.display = XOpenDisplay( env ) ) ) {
        weSendError( WE_ERROR_OPEN_DISPLAY );
        return WE_FAILURE;
    }
    wgl.screen = DefaultScreen( wgl.display );
    if ( wgl.screen ) {
        XCloseDisplay( wgl.display );
        weSendError( WE_ERROR_OPEN_DISPLAY );
        return WE_FAILURE;
    }
    XF86VidModeQueryVersion( wgl.display, &vme_major, &vme_minor );
    if ( !counter ) {
        printf( "Supported XF86VidModeExtension version %d.%d\n", 
            vme_major, vme_minor );
    }
    XF86VidModeGetAllModeLines( wgl.display, wgl.screen, &modeNum, &modes );
    if ( engine->fullscreen ) {
        wgl.deskMode = *modes[0];
        for ( i = 0; i < modeNum; i++ ) {
            if ( ( modes[i]->hdisplay == engine->width ) && 
                ( modes[i]->vdisplay == engine->height ) ) {
                bestMode = i;
            }
        }
    }
    if ( !glXQueryExtension( wgl.display, 0, 0 ) ) {
        XCloseDisplay( wgl.display );
        weSendError( WE_ERROR_GLX_SUPPORT );
        return WE_FAILURE;
    }
    glXQueryVersion( wgl.display, &glx_major, &glx_minor );
    if ( !counter ) {
        printf("Supported GLX version - %d.%d\n", glx_major, glx_minor);
    }
    if ( glx_major == 1 && glx_minor < 3 ) {
        XCloseDisplay( wgl.display );
        weSendError( WE_ERROR_GLX_VERSION);
        return WE_FAILURE;
    }
    return WE_NULL;
}

int weLoop( void )
{
    return WE_NULL;
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

