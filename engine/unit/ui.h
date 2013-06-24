// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  UI
// Description:  Experimental UI Module
//

#ifndef __MODULE_UI__
#define __MODULE_UI__

#ifdef __WIN32__
    #include <windows.h>
    #include <gl/gl.h>
    #include <gl/glu.h>
#elif __linux__
    #include <GL/gl.h>
    #include <GL/glx.h>
#endif

#include <assert.h>
#include <math.h>
#include "font.h"
#include "../error.h"
#include "../structures.h"

typedef void (*ButtonCallback)();

struct uiButton {
    int x, y;
    int w, h;
    int id;
    int state;
    int highlighted;
    char *label;
    ButtonCallback callbackFunc;
    struct uiButton *next;
};
typedef struct uiButton uiButton;

/* export function */
int uiButtonCreate( char *label, ButtonCallback cb, int x, int y, int w, int h );
void uiButtonDelete( void );
int uiButtonDeleteByName( char *label );
int uiButtonDeleteById( int id );
int uiButtonClick( uiButton *b, int x, int y );
void uiButtonRelease( int x, int y );
void uiButtonPress( int x, int y );
void uiButtonPassive( int x, int y );
void uiButtonDraw( uiFont *f );
int uiButtonPressedId( void );
void uiButtonChangeLabel( int id, char *label );

#endif