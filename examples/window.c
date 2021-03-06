#include "../engine/kernel.h"
#include "../engine/unit/ui.h"
#include "../engine/unit/font.h"
#include <string.h>

uiFont font;

void ButtonTest01 ( void )
{
    printf( "#01\n" );
}

void ButtonTest02( void )
{
    printf( "#02\n" );
}

void render( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    glLoadIdentity();
    uiButtonDraw( &font );
    glColor3f( 1.0f, 1.0f, 1.0f );
    uiFontPrintf( &font, 10.0f, 490.0f, "FPS: %.2f", weGetFps() );
    uiFontPrintf( &font, 10.0f, 400.0f, "Тестовый текст!" );
    weSwapBuffers();
}

void init( void )
{
    glClearColor( 0.22f, 0.25f, 0.25f, 1.0f );
    uiFontFreeTypeBuild( &font, 14, "OpenSans-Bold.ttf" );
    uiButtonCreate( "Test01", ButtonTest01, 10, 10, 100, 25 );
    uiButtonCreate( "Test02", ButtonTest02, 10, 45, 100, 25 );
    weTimerInit();
    weTimerSet( 30, render );
}

void resize( int width, int height )
{
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f );
    gluPerspective( 0.0f, 0.0f, 0.0f, 100.0f );
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}

void mouse_a( int state, int button, int x, int y )
{
    if ( state == WE_STATE_DOWN ) {
        if ( button == WE_LEFT_BUTTON ) {
            uiButtonPress( x, y );
        }
    }
    if ( state == WE_STATE_UP ) {
        if ( button == WE_LEFT_BUTTON ) {
            uiButtonRelease( x, y );
        }
    }
}

void keyboard( unsigned int *map )
{
    if ( map['w'] || map[WE_KEY_PRINT] ) {
        printf( "Hello, world!\n" );
    }
}

void mouse_m( int x, int y )
{
    uiButtonPassive( x, y );
}

void destroy( void )
{
    weTimerKill();
    uiButtonDelete();
    uiFontKill( &font );
}

int main( int argc, char *argv[] )
{
    weInit( argc, argv );
    weInitWindow( 500, 500, 0 );
    weInitOpenGL( 0 );
    weCreateWindow( "Wrench Engine #1" );
    weRenderFunc( render );
    weResizeFunc( resize );
    weMouseActionFunc( mouse_a );
    weMouseMotionFunc( mouse_m );
    weKeyboardFunc( keyboard );
    init();
    weLoop();
    destroy();
    return 0;
}
