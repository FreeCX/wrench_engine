#include "../engine/kernel.h"
#include <math.h>
#include <time.h>

void get_time( int *hour, int *min, int *sec )
{
	time_t now;
	struct tm * t_info;
	
	now = time( NULL );
	t_info = localtime( &now );
	*hour = t_info->tm_hour;
	*min = t_info->tm_min;
	*sec = t_info->tm_sec;
}

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
	int h, m, s;

	get_time( &h, &m, &s );
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	glTranslatef( 0.0f, 0.0f, 1.0f );
	glPointSize( 5.0f );
	glBegin( GL_POINTS );
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