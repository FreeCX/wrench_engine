// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  GUI
// Last update:  09/03/13
// Description:  Experimental GUI
//

#include "gui.h"

static char *text;

void uiButtonDraw( uiButton *b, uiFont *f )
{
	int fontx, fonty;

	if ( b && f ) {
		glColor3f( 0.6f, 0.6f, 0.6f );
		glBegin( GL_QUADS );
			glVertex2i( b->x     , b->y      );
			glVertex2i( b->x     , b->y+b->h );
			glVertex2i( b->x+b->w, b->y+b->h );
			glVertex2i( b->x+b->w, b->y      );
		glEnd();
		glLineWidth( 3 );
		glColor3f( 0.8f, 0.8f, 0.8f );
		glBegin( GL_LINE_STRIP );
			glVertex2i( b->x+b->w, b->y      );
			glVertex2i( b->x     , b->y      );
			glVertex2i( b->x     , b->y+b->h );
		glEnd();
		glColor3f( 0.4f, 0.4f, 0.4f );
		glBegin( GL_LINE_STRIP );
			glVertex2i( b->x     , b->y+b->h );
			glVertex2i( b->x+b->w, b->y+b->h );
			glVertex2i( b->x+b->w, b->y      );
		glEnd();
		glLineWidth( 1 );
		fontx = b->x + ( b->w - 50 ) / 2 ;
		fonty = b->y + ( b->h + 10 ) / 2;
		glColor3f( 1.0f, 1.0f, 1.0f );
		uiFontPrintf( f, fontx, fonty, b->label );
	}
}

void uiFontBuild( uiFont * f )
{
#ifdef __WIN32__
	HFONT w_font;
	extern HDC hDC;

    f->base = glGenLists( UI_FONT_LIST );
    text = (char *) weMalloc( WE_TEXT_SIZE * sizeof(char) );
    switch ( f->weight ) {
        case UI_FONT_MEDIUM:
            f->weight = FW_MEDIUM;
            break;
        case UI_FONT_BOLD:
            font->weight = FW_BOLD;
            break;
    }
    w_font = CreateFont( -f->size, 0, 0, 0, f->weight, 0, 0, 0, 
        ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 
        ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, f->name );
    if ( !w_font ) {
        w_font = CreateFont( -font->size, 0, 0, 0, f->weight, 0, 0, 0, 
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
	
	text = (char *) weMalloc( WE_TEXT_SIZE * sizeof(char) );
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
    n = vsnprintf( text, WE_TEXT_SIZE, fmt, ap ); 
    va_end( ap );    
    glRasterPos2f( x, y );
    glPushAttrib( GL_LIST_BIT );    
    glListBase( f->base - 32 );    
    glCallLists( n, GL_UNSIGNED_BYTE, text );    
    glPopAttrib();  
}

void uiFontKill( void )
{
    weFree( text );
}