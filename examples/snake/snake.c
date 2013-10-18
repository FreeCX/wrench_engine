#include <string.h>
#include <time.h>
#include "../../engine/kernel.h"
#include "../../engine/unit/ui.h"
#include "../../engine/unit/font.h"
#include "game.h"

uiFont font;

bonus last, znew;
GLfloat fps;
GLuint n = 0;
int pause_game = 1;
int new_game = 0;
extern int game_over;
char lose_text[32] = "";

void render( void );

void init( void )
{
    srand( time( NULL ) );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    uiFontFreeTypeBuild( &font, 14, "../OpenSans-Bold.ttf" );
    game_init( 250, 250, 500, 500 );
    weTimerInit();
    weTimerSet( 30, render );
}

void destroy( void )
{
    weTimerKill();
    uiFontKill( &font );
    game_free();
}

void render( void )
{
    static float alpha = 1.0f;
    static int k = 1;
    glClear( GL_COLOR_BUFFER_BIT );
    glLoadIdentity();

    glPointSize( 8.0f );
    game_draw();

    /* game text info */
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    if (!pause_game && new_game) {
        uiFontPrintf(&font, 180.0f, 240.0f, "GAME PAUSED");
        uiFontPrintf(&font, 160.0f, 260.0f, "Press P to continue");
    }
    if (!new_game) {
        uiFontPrintf(&font, 145.0f, 220.0f, lose_text );
        uiFontPrintf(&font, 120.0f, 240.0f, "Press P to start new game");
    }
    /* adding point nice effect */
    glColor3f( 1.0f, 1.0f, 1.0f );
    if ( last.active && last.b_count ) {
        uiFontPrintf( &font, last.x, last.y, "%d", last.point);
        last.y -= 100.0f / fps;
    }
    /* main code */
    if ( fps && n >= fps / 6 && pause_game && new_game ) {
        player_move();
        player_colision();
        eat_refresh();
        znew = get_last_bonus();
        if (znew.update) {
            last = get_last_bonus();
            last.update = 0;
            set_last_bonus(last);
        }
        if (last.b_count == 0) {
            last.active = 0;
            last.b_count = 0;
            set_last_bonus(last);
        }
        if (last.active) {
            last.b_count--;
        }
        if (game_over) {
            new_game = 0;
            game_over = 0;
            sprintf( lose_text, "Kicked by blue wall" );
        }
        n = 0;
    } else {
        n++;
    }

    if ( alpha < 0.6f ) {
        k = -k;
    }
    if ( alpha > 1.0f ) {
        k = -k;
    }
    alpha -= k*0.025f;

    glColor3f( 1.0f, 1.0f, 1.0f );
    uiFontPrintf( &font, 10.0f, 490.0f, "FPS: %.2f", fps );
    uiFontPrintf( &font, 10.0f, 20.0f, "point: %d", player_point() );
    uiFontPrintf( &font, 10.0f, 40.0f, "count: %d", player_count() );

    weSwapBuffers();

    fps = weGetFps();
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

void keyboard( unsigned int *map )
{
    if ( map['w'] ) {
        player_direction(MOVE_UP);
    }
    if ( map['s'] ) {
        player_direction(MOVE_DOWN);
    }
    if ( map['a'] ) {
        player_direction(MOVE_LEFT);
    }
    if ( map['d'] ) {
        player_direction(MOVE_RIGHT);
    }
    if ( map['p'] ) {
        if ( !new_game ) { 
            new_game = 1; 
            game_over = 0;
        } else {
            pause_game = !pause_game;
        }
    }
}

int main( int argc, char *argv[] )
{
    weInit( argc, argv );
    weInitWindow( 500, 500, 0 );
    weInitOpenGL( 0 );
    weCreateWindow( "Snake The Game" );
    weRenderFunc( render );
    weResizeFunc( resize );
    weKeyboardFunc( keyboard );
    init();
    weLoop();
    destroy();
    return 0;
}
