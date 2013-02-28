#include <math.h>
#include "../engine/kernel.h"

void init( void )
{
	glClearColor( 0.3f, 0.3f, 0.4f, 1.0f );
}

void resize( int width, int height )
{
	GLfloat param1, n = 2.0f;

	param1 = (float)width/height;
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	if ( width <= height ) {
		glOrtho( -n, n, -n/param1, n/param1, n, -n );
	} else {
		glOrtho( -n * param1, n * param1, -n, n, n, -n );
	}
	gluPerspective( 0.0f, param1, 0.0f, 10.0f );
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}

void render( void )
{
	static float t = 0.0f, n = 0.0f;

	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	glTranslatef( 0.0f, 0.0f, 1.0f );
	glPointSize( 5.0f );
	glBegin( GL_POINTS );
	for ( n = 0.0f; n < M_PI; n += 0.01f ) {
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex2f( 1.0f * sin( t + n ), 1.0f * cos( t + n ) );
		glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex2f( 0.8f * sin( 1.0f - t + n ), 0.8f * cos( 1.0f - t + n ) );
		glColor3f( 0.0f, 0.0f, 1.0f );
		glVertex2f( 0.6f * sin( t + n + 1.0f ), 0.6f * cos( t + n + 1.0f ) );
	}
	glEnd();
	weSwapBuffers();
	t += 0.05f;
}

int main( int argc, char *argv[] )
{
	weInit( argc, argv );
	weInitWindow( 500, 500, 0 );
	weInitOpenGL( 0 );
	weCreateWindow( "Wrench Engine #1" );
	weRenderFunc( render );
	weResizeFunc( resize );
	init();
	weLoop();
	return 0;
}