// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Font
// Last update:  25/03/13
// Description:  Experimental Font Module
//

#include "font.h"

static char text[UI_TEXT_SIZE];

void uiFontBuild( uiFont * f )
{
#ifdef __WIN32__
    HFONT w_font;
    extern HDC hDC;

    f->base = glGenLists( UI_FONT_LIST );
    switch ( f->weight ) {
        case UI_FONT_MEDIUM:
            f->weight = FW_MEDIUM;
            break;
        case UI_FONT_BOLD:
            f->weight = FW_BOLD;
            break;
    }
    w_font = CreateFont( -f->size, 0, 0, 0, f->weight, 0, 0, 0, 
        ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 
        ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, f->name );
    if ( !w_font ) {
        w_font = CreateFont( -f->size, 0, 0, 0, f->weight, 0, 0, 0, 
            ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 
            ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Arial" );
        weModuleError( "Can't load font!" );
    }
    SelectObject( hDC, w_font );
    wglUseFontBitmaps( hDC, 32, UI_FONT_LIST, f->base );
    /* C++ error mode on */
    if ( sizeof('a') == sizeof(char) ) {
        wglUseFontBitmaps( hDC, 32, UI_FONT_LIST, f->base );
    }
#elif __linux__
    XFontStruct *x_font; 
    Display *dsp;   
    char buffer[128];
    char type[16];

    switch ( f->weight ) {
        case UI_FONT_BOLD:
            sprintf( type, "bold" );
            break;
        case UI_FONT_MEDIUM:
            sprintf( type, "medium" );
            break;
    }
    sprintf( buffer, "-*-%s-%s-r-normal--%d-*-*-*-c-*-iso8859-1", f->name, 
        type, f->size);
    dsp = XOpenDisplay( NULL );
    f->base = glGenLists( UI_FONT_LIST ); /* storage for 96 characters */       
    x_font = XLoadQueryFont( dsp, buffer );    
    if ( x_font == NULL ) {
        x_font = XLoadQueryFont( dsp, "fixed" );    
        if ( x_font == NULL ){    
            weModuleError( "Can't load font!" );
            return;
        }    
    }    
    glXUseXFont( x_font->fid, 32, UI_FONT_LIST, f->base );    
    XFreeFont( dsp, x_font );  
#endif
}

void uiFontPrintf( uiFont *f, float x, float y, const char *fmt, ... )
{
    /* нужна оптимизация скорости вывода текста */
    va_list ap;
    int n;

    if ( fmt == NULL ) {
        return;
    }
    va_start( ap, fmt);
    n = vsnprintf( text, UI_TEXT_SIZE, fmt, ap ); 
    va_end( ap );    
    glRasterPos2f( x, y );
    glPushAttrib( GL_LIST_BIT );    
    glListBase( f->base - 32 );    
    glCallLists( n, GL_UNSIGNED_BYTE, text );    
    glPopAttrib();  
}

void uiFontKill( uiFont *f )
{
    glDeleteLists( f->base, UI_FONT_LIST );
}