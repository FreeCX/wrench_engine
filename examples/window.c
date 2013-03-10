#include "../engine/kernel.h"
#include "../engine/gui.h"

int b01, b02;
uiFont font = { 14, 14, "Terminus", 0 };

void ButtonTest01 ( void )
{
	printf( "#01\n" );
}

void ButtonTest02( void )
{
	printf( "#02\n" );
}

void init( void )
{
	glClearColor( 0.3f, 0.3f, 0.4f, 1.0f );
	uiFontBuild( &font );
	b01 = uiButtonCreate( "Test01", ButtonTest01, 10, 10, 100, 25 );
	b02 = uiButtonCreate( "Test02", ButtonTest02, 10, 45, 100, 25 );
}

void render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	uiButtonDraw( &font );
	weSwapBuffers();
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

void mouse( int state, int button, int x, int y )
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

void destroy( void )
{
	uiButtonDeleteById( b01 );
	uiButtonDeleteById( b02 );
	uiFontKill();
}

int main( int argc, char *argv[] )
{
	weInit( argc, argv );
	weInitWindow( 500, 500, 0 );
	weInitOpenGL( 0 );
	weCreateWindow( "Wrench Engine #1" );
	weRenderFunc( render );
	weResizeFunc( resize );
	weMouseFunc( mouse );
	init();
	weLoop();
	destroy();
	return 0;
}