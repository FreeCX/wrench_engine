// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Window
// Last update:  26/03/13
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

void ( *render_context_callback )( void );
void ( *resize_context_callback )( int, int );
void ( *mouse_action_callback )( int, int, int, int );
void ( *mouse_motion_callback )( int, int );

static we_window_t wgl;
char *buffer;
int fullscreen = WE_FALSE, running = WE_TRUE;
int window_width, window_height;
int *x_pos, *y_pos;
extern int __DEBUG__;

int weInitWindow( const int width, const int height, const int flag )
{
    window_width = width;
    window_height = height;
    buffer = (char *) weCalloc( 256, sizeof(char) );
    return WE_NULL;
}

int weInitOpenGL( const int glFlag )
{
    return WE_NULL;
}

int weCreateWindow( const char *title )
{
    static int counter = 0;
    XF86VidModeModeInfo **modes;
    int glx_major, glx_minor;
    int vme_major, vme_minor;
    int modeNum, bestMode, i;
    int s_width, s_height;
    Atom wmDelete;
    char *env = getenv("DISPLAY");

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
        printf( "Supported XF86VidModeExtension version - %d.%d\n", 
            vme_major, vme_minor );
    }
    XF86VidModeGetAllModeLines( wgl.display, wgl.screen, &modeNum, &modes );
    if ( fullscreen ) {
        wgl.deskMode = *modes[0];
        for ( i = 0; i < modeNum; i++ ) {
            if ( ( modes[i]->hdisplay == window_width ) && 
                ( modes[i]->vdisplay == window_height ) ) {
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
        wgl.window = XCreateWindow( wgl.display, wgl.root, 0, 0, 
            window_width, window_height, 0, wgl.vInfo->depth, InputOutput, 
            wgl.vInfo->visual, CWBorderPixel | CWColormap | CWEventMask, 
            &wgl.setWindowAttr );
        if ( !wgl.window ) {
            weSendError( WE_ERROR_CREATE_WINDOW );
            XCloseDisplay( wgl.display );
            return WE_EXIT_FAILURE;
        }
        if ( __DEBUG__ ) {
            printf("> Window mode: %dx%dx%d\n", window_width, 
                window_height, wgl.vInfo->depth);
        }
        wmDelete = XInternAtom( wgl.display, "WM_DELETE_WINDOW", True );
        XSetWMProtocols( wgl.display, wgl.window, &wmDelete, 1 );
        XSetStandardProperties( wgl.display, wgl.window, title, title, 
            None, NULL, 0, NULL );
        XMapRaised( wgl.display, wgl.window );
    }
    wgl.context = glXCreateContext( wgl.display, wgl.vInfo, 0, 1 );
    if ( !wgl.context ) {
        weSendError( WE_ERROR_CREATE_CONTEXT );
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

int weLoop( void )
{
    XEvent event;
    uint now = 0, start = 0, stop = 1000 / 60;
    int mouse_state, mouse_button, mouse_active = WE_FALSE;

    if ( resize_context_callback ) {
        resize_context_callback( window_width, window_height );
    }
    XSelectInput( wgl.display, wgl.window, PointerMotionMask | 
        ButtonPressMask | ButtonReleaseMask | ButtonPress | 
        ButtonRelease | KeyPressMask | KeyReleaseMask | StructureNotifyMask );
    while ( running ) {
        while ( XPending( wgl.display ) ) {
            XNextEvent( wgl.display, &event );
            switch ( event.type ) {
                case ConfigureNotify:
                    if ( resize_context_callback ) {
                        resize_context_callback( event.xconfigure.width, 
                            event.xconfigure.height );
                    }
                    break;
                case Expose:
                    XGetWindowAttributes( wgl.display, wgl.window, &wgl.windowAttr );
                    if ( resize_context_callback ) {
                        resize_context_callback( wgl.windowAttr.width, 
                            wgl.windowAttr.height );
                    }
                    break;
                case ButtonPress:
                    mouse_state = WE_STATE_DOWN;
                    mouse_button = event.xbutton.button;
                    mouse_active = WE_TRUE;
                    break;
                case ButtonRelease:
                    mouse_state = WE_STATE_UP;
                    mouse_button = event.xbutton.button;
                    mouse_active = WE_TRUE;
                    break;
                case ClientMessage:
                    running = WE_FALSE;
                    break;
            }
        }
        /* need a update this rendering callback code */
        now = weTicks();
        if ( render_context_callback && ( now - start > stop ) ) {
            start = weTicks();
            x_pos = &event.xmotion.x;
            y_pos = &event.xmotion.y;
            if ( mouse_action_callback && mouse_active ) {
                mouse_action_callback( mouse_state, mouse_button, *x_pos, *y_pos );
                mouse_active = WE_FALSE;
            }
            if ( mouse_motion_callback ) {
                mouse_motion_callback( *x_pos, *y_pos );
            }
            render_context_callback();
        }
        usleep( 1200 );
    }
    weKill();
    return WE_EXIT_SUCCESS;
}

void weKill( void )
{
    running = 0;
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
    weFree( buffer );
}

void weSwapBuffers( void )
{
    glXSwapBuffers( wgl.display, wgl.window );
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

void weGetCursorPos( int *x, int *y )
{
    *x = *x_pos;
    *y = *y_pos;
}

void weRedraw( void )
{
    if ( render_context_callback ) {
        render_context_callback();
    }
}

void weRenderFunc( void ( *param )( void ) ) 
{
    render_context_callback = param;
}

void weResizeFunc( void ( *param )( int, int ) )
{
    resize_context_callback = param;
}

void weMouseActionFunc( void ( *param )( int, int, int, int ))
{
    mouse_action_callback = param;
}

void weMouseMotionFunc( void ( *param )( int, int ))
{
    mouse_motion_callback = param;
}