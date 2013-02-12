// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Window
// Last update:  12/02/13
// Description:  Window system (linux)
//

#include "linux.h"

/* need a rewrite this to use mask param */
static int single_attr[] = {
    GLX_RGBA,
    GLX_DEPTH_SIZE, 24,
    GLX_RED_SIZE, 4,
    GLX_GREEN_SIZE, 4,
    GLX_BLUE_SIZE, 4,
    None
};
static int double_attr[] = {
    GLX_RGBA,
    GLX_DOUBLEBUFFER,
    GLX_DEPTH_SIZE, 24,
    GLX_RED_SIZE, 4,
    GLX_GREEN_SIZE, 4,
    GLX_BLUE_SIZE, 4,
    None
};

static we_window_t wgl;
static char buffer[WE_TEXT_SIZE];
static char def_name[] = "Wrench Engine Window";
extern int __DEBUG__;

int weInitOpenGL( const int glFlag )
{
    return WE_NULL;
}

int weCreateWindow( const int width, const int height, const int fullscreen, 
    const int debug )
{
    static int counter = 0;
    XF86VidModeModeInfo **modes;
    int glx_major, glx_minor;
    int vme_major, vme_minor;
    int modeNum, bestMode, i;
    int s_width, s_height;
    Atom wmDelete;
    char *env = getenv("DISPLAY");

    __DEBUG__ = debug;
    if ( !( wgl.display = XOpenDisplay( env ) ) ) {
        weSendError( WE_ERROR_OPEN_DISPLAY );
        return WE_EXIT_FAILURE;
    }
    wgl.screen = DefaultScreen( wgl.display );
    if ( wgl.screen ) {
        XCloseDisplay( wgl.display );
        weSendError( WE_ERROR_OPEN_DISPLAY );
        return WE_EXIT_FAILURE;
    }
    XF86VidModeQueryVersion( wgl.display, &vme_major, &vme_minor );
    if ( !counter ) {
        printf( "Supported XF86VidModeExtension version %d.%d\n", 
            vme_major, vme_minor );
    }
    XF86VidModeGetAllModeLines( wgl.display, wgl.screen, &modeNum, &modes );
    if ( fullscreen ) {
        wgl.deskMode = *modes[0];
        for ( i = 0; i < modeNum; i++ ) {
            if ( ( modes[i]->hdisplay == width ) && 
                ( modes[i]->vdisplay == height ) ) {
                bestMode = i;
            }
        }
    }
    if ( !glXQueryExtension( wgl.display, 0, 0 ) ) {
        XCloseDisplay( wgl.display );
        weSendError( WE_ERROR_GLX_SUPPORT );
        return WE_EXIT_FAILURE;
    }
    glXQueryVersion( wgl.display, &glx_major, &glx_minor );
    if ( !counter ) {
        printf("Supported GLX version - %d.%d\n", glx_major, glx_minor);
    }
    if ( glx_major == 1 && glx_minor < 3 ) {
        XCloseDisplay( wgl.display );
        weSendError( WE_ERROR_GLX_VERSION);
        return WE_EXIT_FAILURE;
    }
    /* using mask param to select OpenGL attributes */
    wgl.vInfo = glXChooseVisual( wgl.display, 0, double_attr );
    if ( wgl.vInfo == NULL ) {
        wgl.vInfo = glXChooseVisual( wgl.display, 0, single_attr );
        if ( wgl.vInfo == NULL ) {
            weSendError( WE_ERROR_CHOOSE_VISUAL );
            return WE_EXIT_FAILURE;
        }
    }
    wgl.root = RootWindow( wgl.display, wgl.vInfo->screen );
    wgl.setWindowAttr.colormap = XCreateColormap( wgl.display, 
        wgl.root, wgl.vInfo->visual, AllocNone );
    wgl.setWindowAttr.event_mask = ExposureMask | KeyPressMask | 
        ButtonPressMask;
    if ( fullscreen ) {
        XF86VidModeSwitchToMode( wgl.display, wgl.screen, modes[bestMode] );
        XF86VidModeSetViewPort( wgl.display, wgl.screen, 0, 0 );
        s_width = modes[bestMode]->hdisplay;
        s_height = modes[bestMode]->vdisplay;
        if ( __DEBUG__ ) {
            printf("> Fullscreen Mode: %dx%dx%d\n", s_width, s_height, 
                wgl.vInfo->depth);
        }
        XFree( modes );
        wgl.setWindowAttr.override_redirect = 1;
        wgl.window = XCreateWindow( wgl.display, wgl.root, 0, 0, s_width, s_height, 
            0, wgl.vInfo->depth, InputOutput, wgl.vInfo->visual, 
            CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, 
            &wgl.setWindowAttr );
        if ( !wgl.window ) {
            weSendError( WE_ERROR_CREATE_WINDOW );
            XCloseDisplay( wgl.display );
            return WE_EXIT_FAILURE;
        }
        XMapRaised( wgl.display, wgl.window );
        XGrabKeyboard( wgl.display, wgl.window, 1, GrabModeAsync, GrabModeAsync, 
            CurrentTime );
        XGrabPointer( wgl.display, wgl.window, 1, ButtonPressMask, 
            GrabModeAsync, GrabModeAsync, wgl.window, None, CurrentTime );
    } else {
        wgl.setWindowAttr.border_pixel = 0;
        wgl.window = XCreateWindow( wgl.display, wgl.root, 0, 0, width, height, 
            0, wgl.vInfo->depth, InputOutput, wgl.vInfo->visual, 
            CWBorderPixel | CWColormap | CWEventMask, &wgl.setWindowAttr );
        if ( !wgl.window ) {
            we_error_send( WE_ERROR_CREATE_WINDOW );
            XCloseDisplay( wgl.display );
            return WE_EXIT_FAILURE;
        }
        if ( __DEBUG__ ) {
            printf("> Window mode: %dx%dx%d\n", width, height, wgl.vInfo->depth);
        }
        wmDelete = XInternAtom( wgl.display, "WM_DELETE_WINDOW", True );
        XSetWMProtocols( wgl.display, wgl.window, &wmDelete, 1 );
        XSetStandardProperties( wgl.display, wgl.window, def_name, def_name, 
            None, NULL, 0, NULL );
        XMapRaised( wgl.display, wgl.window );
    }
    wgl.context = glXCreateContext( wgl.display, wgl.vInfo, 0, 1 );
    if ( !wgl.context ) {
        we_error_send( WE_ERROR_CREATE_CONTEXT );
        XCloseDisplay( wgl.display );
        return WE_EXIT_FAILURE;
    }
    if ( !glXMakeCurrent( wgl.display, wgl.window, wgl.context ) ) {
        weSendError( WE_ERROR_DRAW_CONTEXT );
        glXDestroyContext( wgl.display, wgl.context );
        wgl.context = WE_NULL;
        return WE_EXIT_FAILURE;
    }
    counter++;
    return WE_EXIT_SUCCESS;
}

void weSetCaption( const char *fmt, ... )
{
    va_list text;
    XTextProperty wn;
    int count = 0;
    
    if ( fmt == NULL ) {
        return ;
    }
    va_start( text, fmt );
    count = vsnprintf( buffer, WE_TEXT_SIZE, fmt, text ); 
    va_end( text ); 
    if ( XStringListToTextProperty( &buffer, 1, &wn ) == 0) {
        return ;
    }
    XSetWMName( wgl.display, wgl.window, &wn );
    XFree( wn.value );
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

