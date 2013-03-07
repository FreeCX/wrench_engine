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
	glPointSize( 3.0f );
	glBegin( GL_POINTS );
	for ( n = -3.9f*M_PI; n < 14.1f*M_PI; n += 0.1f ) {
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex2f( 0.6f * cosf( -( 6.0f * (s+n) * M_PI ) / 180.0f), 
			0.6f * sinf( -( 6.0f * (s+n) * M_PI ) / 180.0f) );
		glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex2f( 0.8f * cosf( -( 6.0f * (m+n) * M_PI ) / 180.0f), 
			0.8f * sinf( -( 6.0f * (m+n) * M_PI ) / 180.0f) );
		glColor3f( 0.0f, 0.0f, 1.0f );
		glVertex2f( cosf( -( 15.0f * (h+n) * 0.4f * M_PI ) / 180.0f + 1.35f ), 
			sinf( -( 15.0f * (h+n) * 0.4f * M_PI ) / 180.0f + 1.35f ) );
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