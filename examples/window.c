#include "../engine/kernel.h"
#include "../engine/gui.h"

void MyButTest( void )
{
	printf( "Hi Jack!\n" );
}

uiButton MyBut = { 10, 10, 100, 25, 0, 0, "The But!", MyButTest };
uiFont font = { 14, 14, "Terminus", 0 };

void init( void )
{
	glClearColor( 0.3f, 0.3f, 0.4f, 1.0f );
	uiFontBuild( &font );
}

void render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	uiButtonDraw( &MyBut, &font );
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
			uiButtonPress( &MyBut, x, y );
		}
	}
	if ( state == WE_STATE_UP ) {
		if ( button == WE_LEFT_BUTTON ) {
			uiButtonRelease( &MyBut, x, y );
		}
	}
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
	uiFontKill();
	return 0;
}