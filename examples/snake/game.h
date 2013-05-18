#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include "../../engine/memory.h"

typedef struct {
	float x, y;
} position;

typedef struct {
	float r, g, b;
} color;

typedef struct {
	float x, y;
	int point;
	int life;
} eat_base;

typedef struct {
    int t_max;
	int count;
	color c;
	position *p;
	int direction;
	int point;
} player;

typedef struct {
	int count;
	color c;
	eat_base *p;
} eat;

typedef struct {
	int count;
	color c;
	position *p;
} wall;

typedef struct {
	int point;
	int b_count;
	int active;
	int update;
	float x, y;
} bonus;

#define MOVE_UP			0
#define MOVE_DOWN		1
#define MOVE_LEFT		2
#define MOVE_RIGHT		3

#define EAT_MAX			50
#define WALL_MAX		50
#define EAT_LIFE		50
#define EAT_POINT		100

void player_move();
void player_add();
void player_direction(int dir);
void player_colision();
int player_point();
int player_count();
color color_set(float r, float g, float b);
void eat_refresh();
void eat_set(int n, int dx, int dy);
void wall_set(int dx, int dy);
bonus get_last_bonus();
void set_last_bonus(bonus a);
int pos_test(float x1, float y1, float x2, float y2);
void game_init( float x, float y, float width, float height );
void game_draw( void );
void game_free( void );

#endif