// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Font
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

#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "../error.h"
#include "../memory.h"

typedef struct {
    int height;
    int weight;
    char * name;
    GLuint * tex;
    GLuint list;
} uiFont;

#define UI_TEXT_SIZE                256
#define UI_FONT_MEDIUM              0
#define UI_FONT_BOLD                1
// #ifdef __WIN32__
// #define UI_FONT_LIST                128
// #elif __linux__
// #define UI_FONT_LIST                0x4FF
// #endif
#define UI_FONT_LIST                0x04FF

/* export function */
void uiFontRasterBuild( uiFont * f, unsigned int height, unsigned int weight, char * font_name );
void uiFontFreeTypeBuild( uiFont *f, unsigned int height, char * font_name );
void uiFontPrintf( uiFont *f, float x, float y, const char *fmt, ... );
void uiFontKill( uiFont *f );

#endif