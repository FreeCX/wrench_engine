// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Window
// Last update:  29/01/13
// Description:  Window system (windows)
//

#include "windows.h"

static HWND hWnd;
static HDC hDC;
static HGLRC hRC; 

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

    if ( ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
    	return WE_NULL;
    }

    return WE_SUCCESS;
}

void SetClientSize( HWND hWnd, const int clientWidth, int const clientHeight )
{
    if ( IsWindow( hWnd ) ) {
        DWORD dwStyle = GetWindowLongPtr( hWnd, GWL_STYLE );
        DWORD dwExStyle = GetWindowLongPtr( hWnd, GWL_EXSTYLE );
        HMENU menu = GetMenu( hWnd );
     
        RECT rc = { 0, 0, clientWidth, clientHeight } ;
     
        if ( !AdjustWindowRectEx( &rc, dwStyle, menu ? TRUE : FALSE, dwExStyle ) ) {
        	MessageBox( NULL, "AdjustWindowRectEx Failed!", "Error", MB_OK );
        }
     
        SetWindowPos( hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
            SWP_NOZORDER | SWP_NOMOVE );
    }
}

int weInitOpenGL( const int mask )
{
    /* insert code */
}

int weCreateWindow( we_engine * engine )
{
	static int count = 0;
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

    if ( count > 0 ) {
    	DestroyWindow( hWnd );
        UnregisterClass( WE_APPCLASS, hInstance );
    }

    if ( !RegisterClass( &wc ) ) {
		weSendError( WE_ERROR_REGISTER_WINDOW );
		return WE_FAILURE;
	}

	/* some code */

    count++;
}

int weLoop( void )
{
    /* insert code */
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

    ReleaseDC(hWnd, hDC);
}

void weSwapBuffers( void )
{
    SwapBuffers(hDC);
}