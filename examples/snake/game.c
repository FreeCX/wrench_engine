#include "game.h"

eat e;
wall w;
bonus b;
player p;
const float delta = 10.0f;
int game_over = 0;
int nf = 0;
int GAME_WIDTH, GAME_HEIGHT, PLAYER_X, PLAYER_Y;

void player_set( float x, float y )
{
	p.p[0].x = x;
	p.p[0].y = y;
	p.count = 1;
	p.direction = MOVE_UP;
	p.point = 0;
	p.c = color_set( 0.51f, 0.58f, 0.59f );
}

void player_move()
{
	int i;

	for (i = p.count; i > 0; i--) {
		p.p[i].x = p.p[i-1].x;
		p.p[i].y = p.p[i-1].y;
	}
	switch (p.direction) {
		case MOVE_UP:
			p.p[0].x += 0;
			p.p[0].y += -delta;
			break;
		case MOVE_DOWN:
			p.p[0].x += 0;
			p.p[0].y += delta;
			break;
		case MOVE_LEFT:
			p.p[0].x += -delta;
			p.p[0].y += 0;
			break;
		case MOVE_RIGHT:
			p.p[0].x += delta;
			p.p[0].y += 0;
			break;
	}
}

void player_add()
{
	position *d = NULL;
    if ( p.t_max == p.count ) {
    	d = (position *) weRealloc( p.p, 2 * p.t_max * sizeof(position) );
    	p.p = d;
    	p.t_max *= 2;
    }
	p.count++;
	p.p[p.count].x = p.p[p.count-1].x;
	p.p[p.count].y = p.p[p.count-1].y;
}

void player_direction(int dir)
{
	p.direction = dir;
}

void player_colision()
{
	int i;
	int point = 0;

	for ( i = 0; i < e.count; i++ ) {
		if ( pos_test( p.p[0].x, p.p[0].y, e.p[i].x, e.p[i].y ) ) {
			p.point += e.p[i].point;
			b.point = e.p[i].point;
    		b.x = e.p[i].x;
    		b.y = e.p[i].y;
    		b.active = 1;
    		b.update = 1;
    		b.b_count = 5;
			eat_set( i, GAME_WIDTH, GAME_HEIGHT );
			player_add();
		}
	}
	for ( i = 1; i < p.count; i++ ) {
		if ( pos_test( p.p[0].x, p.p[0].y, p.p[i].x, p.p[i].y ) ) {
			point = (p.count - i) * EAT_POINT;
			printf("cannibalism: adding %d points!\n", point);
			p.c = color_set( 0.8f, 0.2f, 0.2f );
			p.point += point;
			p.count = i-1;
			b.point = point;
    		b.x = p.p[0].x;
    		b.y = p.p[0].y;
    		b.active = 1;
    		b.update = 1;
    		b.b_count = 5;
		}
	}
	for ( i = 0; i < w.count; i++ ) {
		if ( pos_test( p.p[0].x, p.p[0].y, w.p[i].x, w.p[i].y ) ) {
        	player_set( PLAYER_X, PLAYER_Y );
        	wall_set( GAME_WIDTH, GAME_HEIGHT );
        	eat_set( 0, GAME_WIDTH, GAME_HEIGHT );
			game_over = 1;
		}
	}
	if ( p.p[0].x >= (float)GAME_WIDTH ) {
		p.p[0].x = 0.0f;
	}
	if ( p.p[0].x < 0.0f ) {
		p.p[0].x = (float)GAME_WIDTH;
	}
	if ( p.p[0].y >= (float)GAME_HEIGHT ) {
		p.p[0].y = 0.0f;
	}
	if ( p.p[0].y < 0.0f ) {
		p.p[0].y = (float)GAME_HEIGHT;
	}
}

int player_point()
{
	return p.point;
}

int player_count()
{
	return p.count;
}

color color_set(float r, float g, float b)
{
	color p;
	p.r = r;
	p.g = g;
	p.b = b;
	return p;
}

void eat_refresh()
{
	int i;
	for ( i = 0; i < e.count; i++ ) {
		e.p[i].life--;
		if ( e.p[i].life == 0 ) {
			eat_set( i, GAME_WIDTH, GAME_HEIGHT );
		}
	}
}

void eat_set(int n, int dx, int dy)
{
    int i, flag;
    float xp, yp;

    e.p[n].life = rand()%EAT_LIFE + EAT_LIFE;
    do {
        xp = 1.0f*( rand()%( dx/(int)delta ) * (int)delta );
        yp = 1.0f*( rand()%( dy/(int)delta ) * (int)delta );
        flag = 0;
        /* если flag == 1, то точка уже существует */
        /*
        for (i = 0; (i < p.count && !flag); i++) {
            if (pos_test(p.p[i].x, p.p[i].y, xp, yp) ||
                pos_test(w.p[i].x, w.p[i].y, xp, yp)) {
				flag = 1;
			}
        }
        */
    } while ( flag );
	e.p[n].x = xp;
	e.p[n].y = yp;
	e.p[n].point = rand()%EAT_POINT + 1;
}

void wall_set(int dx, int dy)
{
	int i;

	w.count = rand()%WALL_MAX;
	w.c = color_set( 0.2f, 0.2f, 0.8f );
	w.p = weMalloc( w.count * sizeof(position) );
	for ( i = 0; i < w.count; i++ ) {
		w.p[i].x = ( rand()%( dx/(int)delta ) * (int)delta )*1.0f;
		w.p[i].y = ( rand()%( dy/(int)delta ) * (int)delta )*1.0f;
	}
}


bonus get_last_bonus()
{
	return b;
}

void set_last_bonus(bonus a)
{
	b.active = a.active;
	b.update = a.update;
	b.b_count = a.b_count;
}

int pos_test(float x1, float y1, float x2, float y2)
{
	if (x1 > x2 - delta && x1 < x2 + delta &&
		y1 > y2 - delta && y1 < y2 + delta ) {
		return 1;
	}
	return 0;
}

void game_init( float x, float y, float width, float height )
{
	int i;

	GAME_WIDTH = width;
	GAME_HEIGHT = height;
	PLAYER_X = x;
	PLAYER_Y = y;
    p.t_max = 2;
    p.p = weMalloc( p.t_max * sizeof(position) );
	player_set( PLAYER_X, PLAYER_Y );
	e.count = rand()%EAT_MAX + 10;
	e.p = weMalloc( e.count * sizeof(position) );
	e.c = color_set(0.2f, 0.8f, 0.2f);
	for ( i = 0; i < e.count; i++) {
		eat_set(i, GAME_WIDTH, GAME_HEIGHT );
	}
	wall_set( GAME_WIDTH, GAME_HEIGHT );
}

void game_draw( void )
{
	int i;

	glBegin( GL_POINTS );
	glColor3f( p.c.r, p.c.g, p.c.b );
	for ( i = 0; i < p.count; i++ ) {
		glVertex2f( p.p[i].x, p.p[i].y );
	}
	glColor3f( e.c.r, e.c.g, e.c.b );
	for ( i = 0; i < e.count; i++ ) {
		glVertex2f( e.p[i].x, e.p[i].y );
	}
	glColor3f( w.c.r, w.c.g, w.c.b );
	for ( i = 0; i < w.count; i++ ) {
		glVertex2f( w.p[i].x, w.p[i].y );
	}
	glEnd();
}

void game_free( void )
{
	weFree( p.p );
	weFree( e.p );
	weFree( w.p );
}