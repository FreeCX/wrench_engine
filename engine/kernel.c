// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Kernel
// Description:  The core of the system
//

#include "kernel.h"

static char *engine_name = (char *) "Wrench Engine";
static char *engine_date = (char *) "19/08/14";
static int major_version   = 0;
static int minor_version   = 1;
static int release_version = 0;
static int build_version   = 22;

static int FrameCount = 0;
static float NewCount = 0.0f, LastCount = 0.0f, FpsRate = 0.0f;
w_timer_t *p = NULL;

int __DEBUG_FLAG__ = 0;

static void catch_crash( int signum )
{
#ifdef __WIN32__
    printf( "segmentation violation!\n" );
    getch();
#elif __linux__
    #define STACK_SIZE 128
    void *callstack[STACK_SIZE];
    size_t i, frame;
    char **str;

    frame = backtrace( callstack, STACK_SIZE );
    str = backtrace_symbols( callstack, frame );
    puts( "> backtrace log:" );
    for ( i = 0; i < frame; i++ ) {
        printf( "  %s\n", str[i] );
    }
    free( str );
    signal( signum, SIG_DFL );
#endif
    exit( 3 );
}

int weInit( const int argc, char **argv )
{
    const char* const short_options = "d";
    const struct option long_options[] = {
        { "debug",   0, NULL, 'd' },
        { NULL,      0, NULL, 0 }
    };
    int next_option;
    
    signal( SIGSEGV, catch_crash );
    weInfo();
    do {
        next_option = getopt_long( argc, argv, short_options, long_options, NULL );
        switch ( next_option ) {
            case 'd':
                __DEBUG_FLAG__ = 1;
                puts( "> Debug mode: [on]" );
                break;
            case -1:
                break;
            default:
                abort();
        }
    } while ( next_option != -1 );
    return WE_EXIT_SUCCESS;
}

#ifdef __WIN32__
void weInfo( void )
{
    char buffer[256];
    int dwBuild;
    int dwVersion = GetVersion();
    int dwMajor = ( LOBYTE( LOWORD( dwVersion ) ) );
    int dwMinor = ( HIBYTE( LOWORD( dwVersion ) ) );

    if ( dwVersion < 0x80000000 ) {
        dwBuild = (DWORD)( HIWORD( dwVersion ) );
        sprintf( buffer, "Windows [Version %d.%d.%d]", dwMajor, dwMinor, dwBuild );
    } else if ( dwMajor < 4 ) {
        dwBuild = (DWORD)( HIWORD( dwVersion ) & ~0x8000 ); 
        sprintf( buffer, "WIN32s [Version %d.%d.%d]", dwMajor, dwMinor, dwBuild );
    } else {
        dwBuild = 0;
        sprintf( buffer, "Win95/Win98 [Version %d.%d.%d]", dwMajor, dwMinor, dwBuild );
    }
    printf( "%s %d.%d.%d.%d [%s]\n", engine_name, major_version, minor_version, release_version, build_version, 
            engine_date );
    printf( "Working at %s\n", buffer );
}
#elif __linux__
void weInfo( void )
{
    struct utsname _system;

    printf( "%s %d.%d.%d.%d [%s]\n", engine_name, major_version, minor_version, release_version, build_version, 
            engine_date );
    if ( uname( &_system ) == 0 ) {
        printf( "Working at %s %s %s\n", _system.sysname, _system.release, _system.machine );
    }
}
#endif

void weAbout( char **name, int *major_v, int *minor_v )
{
    *name = engine_name;
    *major_v = major_version;
    *minor_v = minor_version;
}

uint32 weTicks( void )
{
#ifdef __WIN32__
    return timeGetTime();
#elif __linux__
    struct timeval tv;
    gettimeofday( &tv, 0 );
    return ( tv.tv_sec * 1000 + tv.tv_usec / 1000 );
#endif
}

float weGetFps( void )
{
    NewCount = (float) weTicks();
    if ( ( NewCount - LastCount ) > 1000 ) {
        FpsRate = ( FrameCount * 1000 ) / ( NewCount - LastCount );
        LastCount = NewCount;
        FrameCount = 0;
    }
    FrameCount++;
    return FpsRate;
}

void weTimerInit( void )
{
#ifdef __WIN32__
#elif __linux__
    struct itimerval delay;

    signal( SIGALRM, weTimerLoop );
    delay.it_value.tv_sec = 0;
    delay.it_value.tv_usec = 1;
    delay.it_interval.tv_sec = 0;
    delay.it_interval.tv_usec = 1000;
    setitimer( ITIMER_REAL, &delay, NULL );
#endif
}

void weTimerLoop( int signo )
{
    static uint32 a, b;
    w_timer_t *t = p;

    a = b;
    b = weTicks();
    while ( t != NULL ) {
        if ( b - a > 1000 ) {
            t->count++;
        } else {
            t->count += b - a;
        }
        if ( t->count >= t->usec ) {
            t->count = 0;
            t->func();
        }
        t = t->next;
    }
}

void weTimerSet( uint32 usec, void (*func)(void) )
{
    w_timer_t *c;

    c = (w_timer_t *) malloc( sizeof( w_timer_t ) );
    c->usec = usec;
    c->func = func;
    c->next = p;
    p = c;
}

void weTimerKill( void )
{
    w_timer_t *a = p, *c;

    while ( a != NULL ) {
        c = a->next;
        free( a );
        a = c;
    }
}