// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  font
// Last update:  30/04/13
// Description:  Experimental Font Module
//

#include "font.h"

static char text[UI_TEXT_SIZE];

inline int next_p2( int a )
{
    int rval = 1;
    while ( rval < a ) {
        rval <<= 1;
    }
    return rval;
}

void make_dlist( FT_Face face, unsigned char ch, GLuint list, GLuint *tex )
{
    FT_Glyph glyph;
    FT_Bitmap bitmap;
    FT_BitmapGlyph bitmap_glyph;
    int width, height, i, j;
    GLubyte *data;
    float x, y;

    if ( FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), 
        FT_LOAD_RENDER ) ) {
        weModuleError( "FT_Load_Glyph" );
    }
    if ( FT_Get_Glyph( face->glyph, &glyph ) ) {
        weModuleError( "FT_Get_Glyph" );
    }
    FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    bitmap_glyph = (FT_BitmapGlyph) glyph;
    bitmap = bitmap_glyph->bitmap;
    width = next_p2( bitmap.width );
    height = next_p2( bitmap.rows );
    data = (GLubyte *) weCalloc( 2*width*height, sizeof(GLubyte) );
    for ( j = 0; j < height; j++) {
        for ( i = 0; i < width; i++ ) {
            data[2 * (i + j * width)] = 255;
            data[2 * (i + j * width) + 1] = 
            (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
        }
    }
    glBindTexture( GL_TEXTURE_2D, tex[ch] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
        GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data );
    weFree( data );
    glNewList( list+ch, GL_COMPILE );
    glBindTexture( GL_TEXTURE_2D, tex[ch] );
    glTranslatef( bitmap_glyph->left, 0, 0 );
    glPushMatrix();
    glTranslatef( 0, bitmap_glyph->top-bitmap.rows, 0 );
    x = (float) bitmap.width / (float) width;
    y = (float) bitmap.rows / (float) height;
    glBegin( GL_QUADS );
        glTexCoord2d( 0, 0 ); glVertex2f( 0, bitmap.rows );
        glTexCoord2d( 0, y ); glVertex2f( 0, 0 );
        glTexCoord2d( x, y ); glVertex2f( bitmap.width, 0 );
        glTexCoord2d( x, 0 ); glVertex2f( bitmap.width, bitmap.rows );
    glEnd();
    glPopMatrix();
    glTranslatef( face->glyph->advance.x >> 6, 0, 0 );
    glEndList();
    FT_Done_Glyph( glyph );
}

void uiFontRasterBuild( uiFont * f, unsigned int height, unsigned int weight, char *font_name )
{
#ifdef __WIN32__
    HFONT w_font;
    extern HDC hDC;

    f->height = height;
    f->weight = weight;
    f->name = font_name;
    f->list = glGenLists( UI_FONT_LIST );
    switch ( f->weight ) {
        case UI_FONT_MEDIUM:
            f->weight = FW_MEDIUM;
            break;
        case UI_FONT_BOLD:
            f->weight = FW_BOLD;
            break;
    }
    w_font = CreateFont( -f->height, 0, 0, 0, f->weight, 0, 0, 0, 
        ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 
        ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, f->name );
    if ( !w_font ) {
        w_font = CreateFont( -f->height, 0, 0, 0, f->weight, 0, 0, 0, 
            ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 
            ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Arial" );
        weModuleError( "Can't load font!" );
    }
    SelectObject( hDC, w_font );
    wglUseFontBitmaps( hDC, 32, UI_FONT_LIST, f->list );
    /* C++ error mode on */
    if ( sizeof('a') == sizeof(char) ) {
        wglUseFontBitmaps( hDC, 32, UI_FONT_LIST, f->list );
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
        type, f->height);
    dsp = XOpenDisplay( NULL );
    f->list = glGenLists( UI_FONT_LIST );      
    x_font = XLoadQueryFont( dsp, buffer );    
    if ( x_font == NULL ) {
        x_font = XLoadQueryFont( dsp, "fixed" );    
        if ( x_font == NULL ){    
            weModuleError( "Can't load font!" );
            return;
        }    
    }    
    glXUseXFont( x_font->fid, 32, UI_FONT_LIST, f->list );    
    XFreeFont( dsp, x_font );  
#endif
}

void uiFontFreeTypeBuild( uiFont * f, unsigned int height, char * font_name )
{
    FT_Library lib;
    FT_Face face;
    unsigned int i;

    f->tex = (GLuint *) weCalloc( UI_FONT_LIST, sizeof(GLuint) );
    f->height = height;
    if ( FT_Init_FreeType( &lib ) ) {
        weModuleError( "FT_Init_FreeType" );
    }
    if ( FT_New_Face( lib, font_name, 0, &face ) ) {
        weModuleError( "FT_New_Face" );
    }
    FT_Set_Char_Size( face, height << 6, height << 6, 96, 96 );
    FT_Select_Charmap( face, FT_ENCODING_UNICODE );
    f->list = glGenLists( UI_FONT_LIST );
    glGenTextures( UI_FONT_LIST, f->tex );
    for ( i = 0; i < UI_FONT_LIST; i++ ) {
        make_dlist( face, i, f->list, f->tex );
    }
    FT_Done_Face( face );
    FT_Done_FreeType( lib );
}

void uiFontPrintf( uiFont *f, float x, float y, const char *fmt, ... )
{
    GLuint fnt = f->list;
    unsigned char text[256];
    va_list ap;
    float modelview_matrix[16];

    if ( fmt == NULL ) {
        *text = 0;
    } else {
        va_start( ap, fmt );
        vsprintf( text, fmt, ap );
        va_end( ap );
    }
    if ( !f->tex ) {
        glPushAttrib( GL_LIST_BIT );
        glListBase( fnt - 32);
        glRasterPos2f( x, y );      
        glCallLists( strlen(text), GL_UNSIGNED_BYTE, text );
        glPopAttrib();
    } else {
        glPushAttrib( GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | 
            GL_TRANSFORM_BIT );
        glMatrixMode( GL_MODELVIEW );
        glDisable( GL_LIGHTING ); 
        glEnable( GL_TEXTURE_2D );
        glDisable( GL_DEPTH_TEST ); 
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glListBase( fnt );
        glGetFloatv( GL_MODELVIEW_MATRIX, modelview_matrix );
        // для вывода нескольких строк
        glPushMatrix();
        glLoadIdentity();
        glMultMatrixf( modelview_matrix );
        glTranslatef( x, y, 0 );
        glRotatef( 180, 1.0f, 0.0f, 0.0f );
        glCallLists( strlen(text), GL_UNSIGNED_BYTE, text );
        glPopMatrix();
        /* для вывода нескольких строк */
        glPopAttrib();
    }
}

void uiFontKill( uiFont * f )
{
    glDeleteLists( f->list, UI_FONT_LIST );
    if ( f->tex ) {
        glDeleteTextures( UI_FONT_LIST, f->tex );
        weFree( f->tex );
    }
}