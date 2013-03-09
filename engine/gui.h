// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  GUI
// Last update:  09/03/13
// Description:  Experimental GUI
//

#ifndef __MODULE_GUI__
#define __MODULE_GUI__

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
#include "error.h"
#include "structures.h"

typedef struct {
	int size;
	int weight;
	char *name;
	GLuint base;
} uiFont;

typedef struct {
	int x, y;
	int w, h;
	char *label;
} uiButton;

#define UI_FONT_MEDIUM              0
#define UI_FONT_BOLD                1
#define UI_FONT_LIST        		96

/* button */
void uiButtonDraw( uiButton *b, uiFont *f );

/* font module */
void uiFontBuild( uiFont *f );
void uiFontPrintf( uiFont *f, float x, float y, const char *fmt, ... );
void uiFontKill( void );

#endif