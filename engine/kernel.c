// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Kernel
// Last update:  19/01/13
// Description:  The core of the system
//

#include "kernel.h"

static char *engine_name = "Wrench Engine";
static char *engine_date = "31/12/12";

static int major_version   = 0;
static int minor_version   = 1;
static int release_version = 0;
static int build_version   = 1;

int __DEBUG__ = 0;

int weInit( const int argc, char **argv )
{
    const char* const short_options = "d";
    const struct option long_options[] = {
        {"debug",   0, NULL, 'd'},
        {NULL,      0, NULL, 0}
    };
    int next_option;
    
    do {
        next_option = getopt_long( argc, argv, short_options, 
            long_options, NULL );
        
        switch ( next_option ) {
            case 'd':
                __DEBUG__ = 1;
                printf("> Debug mode: [on]\n");
                break;
            case -1:
                break;
            default:
                abort();
        }
    } while ( next_option != -1 );

    return WE_SUCCESS;
}

#ifdef __WIN32__
void weInfo( void )
{
    char buffer[256];
    int dwBuild, i;

    int dwVersion = GetVersion();
    int dwMajor = ( LOBYTE( LOWORD( dwVersion ) ) );
    int dwMinor = ( HIBYTE( LOWORD( dwVersion ) ) );

    if ( dwVersion < 0x80000000 ) {
		dwBuild = (DWORD)( HIWORD( dwVersion ) );
		sprintf( buffer, "Windows [Version %d.%d.%d]", 
            dwMajor, dwMinor, dwBuild );
	} else if (dwMajor < 4) {
		dwBuild = (DWORD)( HIWORD( dwVersion ) & ~0x8000 ); 
		sprintf( buffer, "WIN32s [Version %d.%d.%d]", 
            dwMajor, dwMinor, dwBuild );
	} else {
		dwBuild = 0;
		sprintf( buffer, "Win95/Win98 [Version %d.%d.%d]", 
            dwMajor, dwMinor, dwBuild );
	}

    printf( "%s %d.%d.%d.%d [%s]\n", engine_name, major_version, 
        minor_version, release_version, build_version, engine_date );
    printf( "Working at %s\n", buffer );
}
#elif __linux__
void weInfo( void )
{
    struct utsname _system;

    printf( "%s %d.%d.%d.%d [%s]\n", engine_name, major_version, 
        minor_version, release_version, build_version, engine_date );
    if ( !uname( &_system ) ) {
        printf( "Working at %s %s %s\n", _system.sysname, 
            _system.release, _system.machine );
    }
}
#endif

void weAbout( char **name, int *major_v, int *minor_v )
{
    *name = engine_name;
    *major_v = major_version;
    *minor_v = minor_version;
}
