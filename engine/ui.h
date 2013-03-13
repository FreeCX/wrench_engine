// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  UI
// Last update:  12/03/13
// Description:  Experimental UI
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

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include "error.h"
#include "structures.h"

typedef void (*ButtonCallback)();

typedef struct {
	int size;
	int weight;
	char *name;
	GLuint base;
} uiFont;

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

#define UI_FONT_MEDIUM              0
#define UI_FONT_BOLD                1
#define UI_FONT_LIST        		96

/* button */
int uiButtonCreate( char *label, ButtonCallback cb, int x, int y, int w, int h );
void uiButtonDelete( void );
int uiButtonDeleteByName( char *label );
int uiButtonDeleteById( int id );
int uiButtonClick( uiButton *b, int x, int y );
void uiButtonRelease( int x, int y );
void uiButtonPress( int x, int y );
void uiButtonPassive( int x, int y );
void uiButtonDraw( uiFont *f );

/* font module */
void uiFontBuild( uiFont *f );
void uiFontPrintf( uiFont *f, float x, float y, const char *fmt, ... );
void uiFontKill( void );

#endif