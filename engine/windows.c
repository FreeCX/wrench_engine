// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Window
// Last update:  13/02/13
// Description:  Window system (windows)
//

#include "windows.h"

static HWND hWnd;
static HDC hDC;
static HGLRC hRC; 
static PIXELFORMATDESCRIPTOR pfd;
static char buffer[WE_TEXT_SIZE];
int fullscreen = 0;
int window_width, window_height;
extern int __DEBUG__;

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message ) {
		//case /* MESSAGE */
		//	break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return WE_NULL;
}

int ChangeScreenResolution( const int width, const int height, const int bpp )
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

void SetClientSize( HWND hWnd, const int clientWidth, int const clientHeight )
{
    if ( IsWindow( hWnd ) ) {
        DWORD dwStyle = GetWindowLongPtr( hWnd, GWL_STYLE );
        DWORD dwExStyle = GetWindowLongPtr( hWnd, GWL_EXSTYLE );
        HMENU menu = GetMenu( hWnd );
        RECT rc = {0, 0, clientWidth, clientHeight} ;

        if ( !AdjustWindowRectEx( &rc, dwStyle, menu ? TRUE : FALSE, dwExStyle ) ) {
        	MessageBox( NULL, "AdjustWindowRectEx Failed!", "Error", MB_OK );
        }
        SetWindowPos( hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
            SWP_NOZORDER | SWP_NOMOVE );
    }
}

int weInitWindow( const int width, const int height, const int flag )
{
    window_width = width;
    window_height = height;
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
    DWORD dwStyle = WS_CAPTION | WS_VISIBLE | WS_SYSMENU;
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
    if ( !RegisterClass( &wc ) ) {
		weSendError( WE_ERROR_REGISTER_WINDOW );
		return WE_EXIT_FAILURE;
	}
    if ( fullscreen ) {
        /* insert init code */
    } else {
        /* insert init code */
    }
    hWnd = CreateWindowEx( dwExStyle, WE_APPCLASS, title, 
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, 
        window_width, window_height, 0, 0, hInstance, 0); 
    if ( !hWnd ) {
        weSendError( WE_ERROR_CREATE_WINDOW );
        return WE_EXIT_FAILURE;
    }
    ShowWindow( hWnd, SW_SHOW );
    SetForegroundWindow( hWnd );
    SetFocus( hWnd );
    SetClientSize( hWnd, window_width, window_height );
    if ( !( hDC = GetDC( hWnd ) ) ) {
        weSendError( WE_ERROR_DC_CONTEXT );
        return WE_EXIT_FAILURE;
    }
    ZeroMemory( &pfd, sizeof(pfd) );
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    if ( !( iFormat = ChoosePixelFormat( hDC, &pfd ) ) ) {
        weSendError( WE_ERROR_CHOOSE_PIXELFORMAT );
        return WE_EXIT_FAILURE;
    }
    if ( !SetPixelFormat( hDC, iFormat, &pfd ) ) {
        weSendError( WE_ERROR_SET_PIXELFORMAT );
        return WE_EXIT_FAILURE;
    }
    if ( !( hRC = wglCreateContext( hDC ) ) ) {
        weSendError( WE_ERROR_CREATE_CONTEXT );
        return WE_EXIT_FAILURE;
    }
    if ( !wglMakeCurrent( hDC, hRC ) ) {
        weSendError( WE_ERROR_MAKE_CONTEXT );
        return WE_EXIT_FAILURE;
    }
	/* some code */
    counter++;
    return WE_NULL;
}

int weLoop( void )
{
    return WE_NULL;
}

void weKill( void )
{
    if ( !wglMakeCurrent( hDC, NULL ) ) {
        weSendError( WE_ERROR_CLEAR_CONTEXT );
        return;
    }
    if ( !wglDeleteContext( hRC ) ) {
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
    int count;
    
    if ( fmt == NULL ) {
        return ;
    }
    va_start( text, fmt );
    count = vsnprintf( buffer, WE_TEXT_SIZE, fmt, text ); 
    va_end( text ); 
    SetWindowText( hWnd, buffer );
}