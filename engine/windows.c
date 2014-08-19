// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Window
// Description:  Window system (windows)
//

#include "windows.h"

void ( *render_context_callback )( void );
void ( *resize_context_callback )( int, int );
void ( *mouse_action_callback )( int, int, int, int );
void ( *mouse_motion_callback )( int, int );
void ( *keyboard_action_callback )( unsigned int * );

static HWND hWnd;
static HGLRC hRC; 
static PIXELFORMATDESCRIPTOR pfd;
static char buffer[WE_TEXT_SIZE];
HDC hDC;
int fullscreen = WE_FALSE, running = WE_TRUE;
int window_width, window_height;
int x_pos, y_pos;
unsigned int *keyboard_map;
extern int __DEBUG_FLAG__;

static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    int mouse_state, mouse_button, mouse_active;

    switch ( message ) {
        case WM_CLOSE:
            PostQuitMessage( 0 );
            break;
        case WM_SIZE:
            if ( resize_context_callback ) {
                resize_context_callback( LOWORD( lParam ), HIWORD( lParam ) );
            }
            break;
        case WM_KEYDOWN:
            // old code
            // if ( wParam >= 65 && wParam <= 90 ) {
            //     wParam += 32;
            // }
            if ( islower( wParam ) ) {
                wParam = toupper( wParam );
            }
            keyboard_map[wParam] = WE_TRUE;
            if ( keyboard_action_callback ) {
                keyboard_action_callback( keyboard_map );
            }
            break;
        case WM_KEYUP:
            // old code
            // if ( wParam >= 65 && wParam <= 90 ) {
            //     wParam += 32;
            // }
            if ( islower( wParam ) ) {
                wParam = toupper( wParam );
            }
            keyboard_map[wParam] = WE_FALSE;
            if ( keyboard_action_callback ) {
                keyboard_action_callback( keyboard_map );
            }
            break;
        case WM_LBUTTONDOWN:
            mouse_state = WE_STATE_DOWN;
            mouse_button = WE_LEFT_BUTTON;
            mouse_active = WE_TRUE;
            break;
        case WM_LBUTTONUP:
            mouse_state = WE_STATE_UP;
            mouse_button = WE_LEFT_BUTTON;
            mouse_active = WE_TRUE;
            break;
        case WM_MBUTTONDOWN:
            mouse_state = WE_STATE_DOWN;
            mouse_button = WE_MIDDLE_BUTTON;
            mouse_active = WE_TRUE;
            break;
        case WM_MBUTTONUP:
            mouse_state = WE_STATE_UP;
            mouse_button = WE_MIDDLE_BUTTON;
            mouse_active = WE_TRUE;
            break;
        case WM_RBUTTONDOWN:
            mouse_state = WE_STATE_DOWN;
            mouse_button = WE_RIGHT_BUTTON;
            mouse_active = WE_TRUE;
            break;
        case WM_RBUTTONUP:
            mouse_state = WE_STATE_UP;
            mouse_button = WE_RIGHT_BUTTON;
            mouse_active = WE_TRUE;
            break;
        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }
    if ( mouse_active && mouse_action_callback ) {
        mouse_action_callback( mouse_state, mouse_button, x_pos, y_pos );
        mouse_active = 0;
    }
    return WE_NULL;
}

static int ChangeScreenResolution( const int width, const int height, const int bpp )
{
    DEVMODE dm;

    memset( &dm, 0, sizeof( dm ) );
    dm.dmSize = sizeof( dm );
    dm.dmPelsWidth = width;
    dm.dmPelsHeight = height;
    dm.dmBitsPerPel = bpp;
    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    if ( ChangeDisplaySettings( &dm, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL ) {
        return WE_EXIT_FAILURE;
    }
    return WE_EXIT_SUCCESS;
}

static void SetClientSize( HWND hWnd, const int clientWidth, int const clientHeight )
{
    if ( IsWindow( hWnd ) ) {
        DWORD dwStyle = GetWindowLongPtr( hWnd, GWL_STYLE );
        DWORD dwExStyle = GetWindowLongPtr( hWnd, GWL_EXSTYLE );
        HMENU menu = GetMenu( hWnd );
        RECT rc = { 0, 0, clientWidth, clientHeight } ;

        if ( AdjustWindowRectEx( &rc, dwStyle, menu ? TRUE : FALSE, dwExStyle ) == 0 ) {
            MessageBox( NULL, "AdjustWindowRectEx Failed!", "Error", MB_OK );
        }
        SetWindowPos( hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE );
    }
}

int weInitWindow( const int width, const int height, const int flag )
{
    window_width = width;
    window_height = height;
    keyboard_map = (unsigned int *) weCalloc( 256, sizeof( unsigned int ) );
    return WE_NULL;
}

int weInitOpenGL( const int glFlag )
{
    return WE_NULL;
}

int weCreateWindow( const char *title )
{
    static int counter = 0;
    int iFormat = 0;
    char WE_APPCLASS[] = "WRENCH ENGiNE";
    DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_SIZEBOX;
    DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    HINSTANCE hInstance;
    WNDCLASS wc; 

    hInstance = GetModuleHandle( NULL );
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH) GetStockObject ( BLACK_BRUSH );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WE_APPCLASS;
    if ( counter > 0 ) {
        DestroyWindow( hWnd );
        UnregisterClass( WE_APPCLASS, hInstance );
    }
    if ( RegisterClass( &wc ) == 0 ) {
        weSendError( WE_ERROR_REGISTER_WINDOW );
        return WE_EXIT_FAILURE;
    }
    // in progress
    // if ( fullscreen ) {
    //      insert init code 
    // } else {
    //     /* insert init code */
    // }
    hWnd = CreateWindowEx( dwExStyle, WE_APPCLASS, title, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, 
                           window_width, window_height, 0, 0, hInstance, 0 ); 
    if ( hWnd == 0 ) {
        weSendError( WE_ERROR_CREATE_WINDOW );
        return WE_EXIT_FAILURE;
    }
    ShowWindow( hWnd, SW_SHOW );
    SetForegroundWindow( hWnd );
    SetFocus( hWnd );
    SetClientSize( hWnd, window_width, window_height );
    if ( ( hDC = GetDC( hWnd ) ) == 0 ) {
        weSendError( WE_ERROR_DC_CONTEXT );
        return WE_EXIT_FAILURE;
    }
    ZeroMemory( &pfd, sizeof( pfd ) );
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    if ( ( iFormat = ChoosePixelFormat( hDC, &pfd ) ) == 0 ) {
        weSendError( WE_ERROR_CHOOSE_PIXELFORMAT );
        return WE_EXIT_FAILURE;
    }
    if ( SetPixelFormat( hDC, iFormat, &pfd ) == 0 ) {
        weSendError( WE_ERROR_SET_PIXELFORMAT );
        return WE_EXIT_FAILURE;
    }
    if ( ( hRC = wglCreateContext( hDC ) ) == 0 ) {
        weSendError( WE_ERROR_CREATE_CONTEXT );
        return WE_EXIT_FAILURE;
    }
    if ( wglMakeCurrent( hDC, hRC ) == 0 ) {
        weSendError( WE_ERROR_MAKE_CONTEXT );
        return WE_EXIT_FAILURE;
    }
    /* some code */
    counter++;
    return WE_EXIT_SUCCESS;
}

int weLoop( void )
{
    MSG msg;
    uint32 now = 0, start = 0, stop = 1000 / 60;
    
    running = WE_TRUE;
    // timeBeginPeriod( 1 );
    if ( resize_context_callback ) {
        resize_context_callback( window_width, window_height );
    }
    while ( running ) {
        if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
            if ( msg.message == WM_QUIT ) {
                running = WE_FALSE;
            } else {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
        } else {
            now = weTicks();
            if ( now - start > stop ) {
                weGetCursorPos( &x_pos, &y_pos );
                if ( mouse_motion_callback ) {
                    mouse_motion_callback( x_pos, y_pos );
                }
                // if ( render_context_callback ) {
                //     render_context_callback();
                // }
            }
        }
        /* to offload the CPU */
        usleep( 1500 );
    }
    // timeEndPeriod( 15 );
    weKill();
    return WE_EXIT_SUCCESS;
}

void weKill( void )
{
    running = WE_FALSE;
    weFree( keyboard_map );
    if ( wglMakeCurrent( hDC, NULL ) == 0 ) {
        weSendError( WE_ERROR_CLEAR_CONTEXT );
        return;
    }
    if ( wglDeleteContext( hRC ) == 0 ) {
        weSendError( WE_ERROR_DELETE_CONTEXT );
        return;
    }
    ReleaseDC( hWnd, hDC );
}

void weSwapBuffers( void )
{
    SwapBuffers( hDC );
}

void weSetCaption( const char *fmt, ... )
{
    va_list text;
    
    if ( fmt == NULL ) {
        return ;
    }
    va_start( text, fmt );
    vsnprintf( buffer, WE_TEXT_SIZE, fmt, text ); 
    va_end( text ); 
    SetWindowText( hWnd, buffer );
}

void weGetCursorPos( int *x, int *y )
{
    POINT pt;

    GetCursorPos( &pt );
    ScreenToClient( hWnd, &pt );
    if ( pt.x < 0 ) {
        *x = 0;
    } else if ( pt.x > window_width ) {
        *x = window_width;
    } else {
        *x = pt.x;
    }
    if ( pt.y < 0 ) {
        *y = 0;
    } else if ( pt.y > window_height ) {
        *y = window_height;
    } else {
        *y = pt.y;
    }
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

void weMouseActionFunc( void ( *param )( int, int, int, int ) )
{
    mouse_action_callback = param;
}

void weMouseMotionFunc( void ( *param )( int, int ) )
{
    mouse_motion_callback = param;
}

void weKeyboardFunc( void ( *param )( unsigned int * ) )
{
    keyboard_action_callback = param;
}