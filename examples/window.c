#include <math.h>
#include "../engine/kernel.h"

void init( void )
{
	glClearColor( 0.3f, 0.3f, 0.4f, 1.0f );
}

void render( void )
{
	static float t = 0.0f;

	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	glPointSize( 5.0f );
	glBegin( GL_POINTS );
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex2f( sin( t ), cos( t ) );
	glEnd();
	weSwapBuffers();
	t += 0.01f;
}

int main( int argc, char *argv[] )
{
	weInit( argc, argv );
	weInitWindow( 500, 500, 0 );
	weInitOpenGL( 0 );
	weCreateWindow( "Wrench Engine #1" );
	weRenderFunc( render );
	init();
	weLoop();
	return 0;
}