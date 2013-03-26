// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  UI
// Last update:  26/03/13
// Description:  Experimental UI Module
//

#include "ui.h"

static int bGlobalId = 0;
uiButton *pButtonList = NULL;

int uiButtonCreate( char *label, ButtonCallback cb, int x, int y, int w, int h )
{
    uiButton *p = (uiButton *) weMalloc( sizeof(uiButton) );
    assert( p );
    memset( p, 0, sizeof(uiButton) );
    p->x = x; p->y = y;
    p->w = w; p->h = h;
    p->callbackFunc = cb;
    p->label = (char *) weMalloc( strlen(label) + 1 );
    if ( p->label ) {
        sprintf( p->label, label );
    }
    p->next = pButtonList;
    pButtonList = p;
    return p->id = ++bGlobalId;
}

void uiButtonDelete( void )
{
    uiButton *c = pButtonList;
    while ( c != NULL ) {
        if ( c->label ) {
            weFree( c->label );
        }
        weFree( c );
        c = c->next;
    }
}

int uiButtonDeleteByName( char *label )
{
    uiButton *previous = NULL, *curr = pButtonList;
    while ( curr != NULL ) {
        if ( !strcmp( label, curr->label ) ) {
            if( previous ) {
                previous->next = curr->next;
            } else {
                pButtonList = curr->next;
            }
            if ( curr->label ) {
                weFree( curr->label );
            }
            weFree( curr );
            return WE_TRUE;
        }
        previous = curr;
        curr = curr->next;
    }
    return WE_FALSE;
}

int uiButtonDeleteById( int id )
{
    uiButton *previous = NULL, *curr = pButtonList;
    while ( curr != NULL ) {
        if ( id == curr->id ) {
            if ( previous ) {
                previous->next = curr->next;
            } else {
                pButtonList = curr->next;
            }
            if ( curr->label ) {
                weFree( curr->label );
            }
            weFree( curr );
            return WE_TRUE;
        }
        previous = curr;
        curr = curr->next;
    }
    return WE_FALSE;
}

int uiButtonClick( uiButton *b, int x, int y )
{
    if ( b ) {
        if( x > b->x && x < b->x + b->w && 
            y > b->y && y < b->y + b->h ) {
                return WE_TRUE;
        }
    }
    return WE_FALSE;
}

void uiButtonRelease( int x_press, int y_press )
{
    int x_pos, y_pos;
    uiButton *b = pButtonList;

    weGetCursorPos( &x_pos, &y_pos );
    while ( b ) {
        if ( uiButtonClick( b, x_press, y_press ) && 
            uiButtonClick( b, x_pos, y_pos ) ) {
            if ( b->callbackFunc ) {
                b->callbackFunc();
            }
        }
        b->state = WE_FALSE;
        b = b->next;
    }
}

void uiButtonPress( int x, int y )
{
    uiButton *b = pButtonList;
    while ( b ) {
        if ( uiButtonClick( b, x, y ) ) {
            b->state = WE_TRUE;
        }
        b = b->next;
    }
}

void uiButtonPassive( int x, int y )
{
    int redraw = WE_FALSE;
    uiButton *b = pButtonList;
    while ( b ) {
        if ( uiButtonClick( b, x, y ) ) {
            if ( b->highlighted == WE_FALSE ) {
                b->highlighted = WE_TRUE;
                redraw = WE_TRUE;
            }
        } else {
            if ( b->highlighted == WE_TRUE ) {
                b->highlighted = WE_FALSE;
                redraw = WE_TRUE;
            }
        }
        b = b->next;
    }
    if ( redraw ) {
        weRedraw();
    }
}

void uiButtonDraw( uiFont *f )
{
	float fontx, fonty;
    float xpos;
    uiButton *b = pButtonList;

    if ( f == NULL ) {
        return;
    } 

	while ( b ) {
        if ( b->highlighted ) { 
            glColor3f( 0.7f, 0.7f, 0.8f );
        } else { 
            glColor3f( 0.6f, 0.6f, 0.6f );
        }
		glBegin( GL_QUADS );
			glVertex2i( b->x     , b->y      );
			glVertex2i( b->x     , b->y+b->h );
			glVertex2i( b->x+b->w, b->y+b->h );
			glVertex2i( b->x+b->w, b->y      );
		glEnd();
		glLineWidth( 3 );
		if ( b->state ) { 
            glColor3f( 0.4f, 0.4f, 0.4f );
        } else {
            glColor3f( 0.8f, 0.8f, 0.8f );
        }
		glBegin( GL_LINE_STRIP );
			glVertex2i( b->x+b->w, b->y      );
			glVertex2i( b->x     , b->y      );
			glVertex2i( b->x     , b->y+b->h );
		glEnd();
		if ( b->state ) { 
            glColor3f( 0.8f, 0.8f, 0.8f );
        } else {
            glColor3f( 0.4f, 0.4f, 0.4f );
        }
		glBegin( GL_LINE_STRIP );
			glVertex2i( b->x     , b->y+b->h );
			glVertex2i( b->x+b->w, b->y+b->h );
			glVertex2i( b->x+b->w, b->y      );
		glEnd();
		glLineWidth( 1 );
        fontx = b->x + b->w - f->size * strlen(b->label);
		fonty = b->y + ( b->h + 10 ) / 2;
        if ( b->state ) {
            fontx += 2;
            fonty += 2;
        }
        if( b->highlighted ) {
            glColor3f( 0.0f, 0.0f, 0.0f );
            uiFontPrintf( f, fontx, fonty, b->label );
            fontx--;
            fonty--;
        }
		glColor3f( 1.0f, 1.0f, 1.0f );
        uiFontPrintf( f, fontx, fonty, b->label );
        b = b->next;
	}
}