// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Font
// Last update:  26/03/13
// Description:  Experimental Font Module
//

#ifndef __MODULE_FONT__
#define __MODULE_FONT__

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

typedef struct {
	int size;
	int weight;
	char *name;
	GLuint base;
} uiFont;

#define UI_TEXT_SIZE				256
#define UI_FONT_MEDIUM              0
#define UI_FONT_BOLD                1
#define UI_FONT_LIST        		96

void uiFontBuild( uiFont * f, int size, int weight, char *font_name );
void uiFontPrintf( uiFont *f, float x, float y, const char *fmt, ... );
void uiFontKill( uiFont *f );

#endif