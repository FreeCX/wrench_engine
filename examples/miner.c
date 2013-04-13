#include "../engine/kernel.h"
#include "../engine/unit/ui.h"
#include "../engine/unit/font.h"
#include <time.h>

#define SIZE 25
#define COUNT 14
#define MAXIMUM (SIZE + 10) * COUNT

uiFont font;

int pole[COUNT][COUNT];

int get_pole( int i, int j )
{
    int k, m, summ = 0;
    
    if ( !pole[i][j] ) { 
        for ( k = i-1; k < i+1; k++ ) {
            for ( m = j-1; m < j+1; m++ ) {
                summ += pole[k][m];
            }
        }
        return summ;
    } else {
        return -1;
    }
}

void Button( void )
{
    char label[8];
    int i, j;
    
    printf( "Button pressed: %d\n", uiButtonPressedId() );
    i = (uiButtonPressedId() - 1) / COUNT;
    j = uiButtonPressedId() - i * COUNT - 1;
    sprintf(label, "%d", get_pole( i, j ) );
    printf( "%d\n", get_pole( i, j ) );
    uiButtonChangeLabel( uiButtonPressedId(), label );
    if (i > 0 && j > 0 && !pole[i - 1][j - 1]) {
        sprintf(label, "%d", get_pole( i - 1, j - 1 ) );
        uiButtonChangeLabel( uiButtonPressedId() - 15 , label );
    }
    if (i > 0 && !pole[i - 1][j]) {
        sprintf(label, "%d", get_pole( i-1, j ));
        uiButtonChangeLabel( uiButtonPressedId() - 14, label );
    }
    if (i > 0 && j < COUNT - 1 && !pole[i - 1][j + 1]) {
        sprintf(label, "%d", get_pole( i - 1, j + 1 ));
        uiButtonChangeLabel( uiButtonPressedId() - 13, label );
    }
    if (j < COUNT - 1 && !pole[i][j + 1]) {
        sprintf(label, "%d", get_pole( i, j + 1 ) );
        uiButtonChangeLabel( uiButtonPressedId() + 1, label );
    }
    if (i < COUNT - 1 && j < COUNT - 1 && !pole[i + 1][j + 1]) {
        sprintf(label, "%d", get_pole( i + 1, j + 1 ) );
        uiButtonChangeLabel( uiButtonPressedId() + 15, label );
    }
    if (i < COUNT - 1 && !pole[i + 1][j]) {
        sprintf(label, "%d", get_pole( i + 1, j ) );
        uiButtonChangeLabel( uiButtonPressedId() + 14, label );
    }
    if (i < COUNT - 1 && j > 0 && !pole[i + 1][j - 1]) {
        sprintf(label, "%d", get_pole( i + 1, j - 1 ) );
        uiButtonChangeLabel( uiButtonPressedId() + 13, label );
    }
    if (j > 0 && !pole[i][j - 1]) {
        sprintf(label, "%d", get_pole( i, j - 1 ) );
        uiButtonChangeLabel( uiButtonPressedId() - 1, label );
    }
    printf( "[%d, %d]\n", i, j );
}

void init( void )
{
    int i, j, ip, jp;
    
    srand( time( 0 ) );
    glClearColor( 0.22f, 0.25f, 0.25f, 1.0f );
    uiFontBuild( &font, 14, 0, "Terminus" );
    for ( i = 0; i < COUNT; i++ ) {
        for ( j = 0; j < COUNT; j++ ) {
            pole[i][j] = rand()%10;
            if (pole[i][j] == 5) {
                pole[i][j] = 1;
            }
            else {
                pole[i][j] = 0;
            }
        }
    }
    for ( i = 10; i < MAXIMUM; i += 35 ) {
        for ( j = 10; j < MAXIMUM; j += 35 ) {
            ip = (i-10)/35;
            jp = (j-10)/35;
            uiButtonCreate( "", Button, i, j, SIZE, SIZE );
        }
    }
}

void render( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    glLoadIdentity();
    uiButtonDraw( &font );
    glColor3f( 1.0f, 1.0f, 1.0f );
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

void mouse_a( int state, int button, int x, int y )
{
    if ( state == WE_STATE_DOWN ) {
        if ( button == WE_LEFT_BUTTON ) {
            uiButtonPress( x, y );
        }
    }
    if ( state == WE_STATE_UP ) {
        if ( button == WE_LEFT_BUTTON ) {
            uiButtonRelease( x, y );
        }
    }
}

void keyboard( unsigned int *map )
{
    if ( map['w'] || map[WE_KEY_PRINT] ) {
        printf( "Hello, world!\n" );
    }
}

void mouse_m( int x, int y )
{
    uiButtonPassive( x, y );
}

void destroy( void )
{
    uiButtonDelete();
    uiFontKill( &font );
}

int main( int argc, char *argv[] )
{
    weInit( argc, argv );
    weInitWindow( 500, 500, 0 );
    weInitOpenGL( 0 );
    weCreateWindow( "Wrench Engine #1" );
    weRenderFunc( render );
    weResizeFunc( resize );
    weMouseActionFunc( mouse_a );
    weMouseMotionFunc( mouse_m );
    weKeyboardFunc( keyboard );
    init();
    weLoop();
    destroy();
    return 0;
}
