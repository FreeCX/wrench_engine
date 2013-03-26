#include <assert.h>
#include "../engine/kernel.h"
#include "../engine/unit/font.h"

struct gui_window {
	int x, y;
	int width, height;
	char *label;
	int parent_id, id;
	struct gui_window *parent;
	struct gui_window *next;
};

typedef struct gui_window gui_window;

int id_count = 0;

#define GUI_BAR_SIZE			20
#define GUI_BAR_X				5
#define GUI_BAR_Y				GUI_BAR_SIZE - 5

uiFont font;
gui_window *windowList;
int id1, id2, id3, id4, select_id;

int guiCreateWindow( char *label, int x, int y, int width, int height, int parent )
{
	gui_window *p = (gui_window *) weMalloc( sizeof(gui_window) );
	assert( p );
	memset( p, 0, sizeof(gui_window) );

	p->x = x; p->y = y;
	p->width = width; p->height = height;
	p->parent_id = parent;
	p->label = (char *) weMalloc( strlen(label) + 1 );
	if ( label != NULL ) {
		sprintf( p->label, label );
	}
	if ( parent != 0 ) {
		gui_window *b = windowList;
		while ( b != NULL ) {
			if ( b->id != p->parent_id ) {
				b = b->next;
			} else {
				break;
			}
		}
		p->parent = b;
	} else {
		p->parent = NULL;
	}
	p->next = windowList;
	windowList = p;
	return p->id = ++id_count;
}

void guiGetDepth( gui_window *p, int *x_m, int *y_m, int *depth )
{
	gui_window *c;
	*depth = 1;
	*x_m = *y_m = 0;
	if ( p->parent != NULL ) {
		c = p;
		if ( c->parent != NULL ) {
			while ( c != NULL ) {
				if ( c->parent != NULL ) {
					*x_m += c->parent->x;
					*y_m += c->parent->y;
					c = c->parent->parent;
					*depth++;
				} else {
					break;
				}
			}
		}
	} else {
		*depth = 1;
		*x_m = *y_m = 0;
	}
}

void guiDrawWindow()
{
	int x_m, y_m, depth;
	gui_window *p = windowList;

	while ( p != NULL ) {
		guiGetDepth( p, &x_m, &y_m, &depth );
		/*
		glColor3f( 0.6f, 0.6f, 0.6f );
		glBegin( GL_QUADS );
			glVertex2i( x_m + p->x, y_m + p->y );
			glVertex2i( x_m + p->x + p->width, y_m + p->y );
			glVertex2i( x_m + p->x + p->width, y_m + p->y + p->height );
			glVertex2i( x_m + p->x, y_m + p->y + p->height );
		glEnd();
		*/
		glColor3f( 0.4f, 0.4f, 0.4f );
		glBegin( GL_LINES );
			glVertex2i( x_m + p->x, y_m + p->y + depth * GUI_BAR_SIZE );
			glVertex2i( x_m + p->x + p->width, y_m + p->y + depth * GUI_BAR_SIZE );
		glEnd();
		glColor3f( 0.0f, 0.0f, 0.0f );
		glBegin( GL_LINE_STRIP );
			glVertex2i( x_m + p->x, y_m + p->y );
			glVertex2i( x_m + p->x + p->width, y_m + p->y );
			glVertex2i( x_m + p->x + p->width, y_m + p->y + p->height );
			glVertex2i( x_m + p->x, y_m + p->y + p->height );
			glVertex2i( x_m + p->x, y_m + p->y );
		glEnd();
		uiFontPrintf( &font, x_m + p->x + depth * GUI_BAR_X, y_m + p->y + depth * GUI_BAR_Y, p->label );
		p = p->next;
	}
}

void guiWindowSet( int id, int x, int y )
{
	int x_m, y_m, depth;
	gui_window *p = windowList, *c;

	while ( p != NULL ) {
		if ( p->id == id ) {
			guiGetDepth( p, &x_m, &y_m, &depth );
			p->x = x - x_m - ( depth - 1 ) * GUI_BAR_X;
			p->y = y - y_m - ( depth - 1 ) * GUI_BAR_SIZE;
		}
		p = p->next;
	}
}

int guiWindowPress( int x, int y )
{
	int x_m, y_m, depth;
	gui_window *p = windowList;

	while ( p != NULL ) {
		guiGetDepth( p, &x_m, &y_m, &depth );
        if ( x > p->x + x_m && x < p->x + p->width + x_m && 
        	 y > p->y + y_m && y < p->y + depth * GUI_BAR_SIZE + y_m ) {
			return p->id;
		} 
		p = p->next;
	}
}

void system_init( void )
{
	glClearColor( 0.30f, 0.30f, 0.30f, 1.0f );
	uiFontBuild( &font, 14, 0, "Terminus" );
	id1 = guiCreateWindow( "Parent1", 10, 10, 450, 400, 0 );
	id2 = guiCreateWindow( "Parent2 - Child1", 10, 30, 200, 350, id1 );
	id3 = guiCreateWindow( "Parent2 - Child2", 230, 30, 200, 350, id1 );
	id4 = guiCreateWindow( "Child3", 50, 50, 50, 50, id3 );
	guiCreateWindow( "Window1", 10, 10, 200, 200, 0 );
	guiCreateWindow( "Window2", 220, 10, 200, 200, 0 );
}

void system_render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	guiDrawWindow( );
	weSwapBuffers();
}

void system_resize( int width, int height )
{
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f );
	gluPerspective( 0.0f, 0.0f, 0.0f, 100.0f );
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}

void system_destroy( void )
{
	uiFontKill( &font );
}

void system_mouse_action( int state, int button, int x, int y )
{
	if ( state == WE_STATE_DOWN ) {
		if ( button == WE_LEFT_BUTTON ) {
			select_id = guiWindowPress( x, y );
		}
	}
	if ( state == WE_STATE_UP ) {
		if ( button == WE_LEFT_BUTTON ) {
			select_id = 0;
		}
	}
}

void system_mouse_motion( int x, int y )
{
	if ( select != 0 ) {
		guiWindowSet( select_id, x, y );
	}
}

int main( int argc, char *argv[] )
{
	weInit( argc, argv );
	weInitWindow( 500, 500, 0 );
	weInitOpenGL( 0 );
	weCreateWindow( "GUI Test" );
	weRenderFunc( system_render );
	weResizeFunc( system_resize );
	weMouseActionFunc( system_mouse_action );
	weMouseMotionFunc( system_mouse_motion );
	system_init();
	weLoop();
	system_destroy();
	return 0;
}