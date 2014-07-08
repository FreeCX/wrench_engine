// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Error
// Description:  Error handling system
//

#include "error.h"

static int last_error = 0;
static char str_error[] = "> ERROR: %s\n";

static char *str_error_msg[] = {
    (char *) "No error",
    (char *) "Can't allocate memory",
    
    (char *) "Release of DC and RC failed",
    (char *) "Release Rendering Context Failed",
    (char *) "Failed to register the Window class",
    (char *) "Window creation error",
    (char *) "Couldn't create GL device context",
    (char *) "Couldn't find suitable PixelFormat",
    (char *) "Couldn't set PixelFormat",
    (char *) "Couldn't create GL rendering context",
    (char *) "Couldn't ativate GL rendering context",

    (char *) "Couldn't release drawing context",
    (char *) "Couldn't open display",
    (char *) "X Server no support GLX Extension",
    (char *) "GLX 1.3 or greater necessary",
    (char *) "Couldn't choose visual context"
};

void weSendError( const int error )
{
    last_error = error;
}

int weGetError( void )
{
    return last_error;
}

char ** weGetErrorString( void )
{
    return &str_error_msg[last_error];
}

void wePrintError( void )
{
    printf( str_error, str_error_msg[last_error] );
}

void weModuleError( const char *format, ... )
{
    va_list list;

    if ( format != NULL ) {
        va_start( list, format );
        vprintf( format, list );
        va_end( list );
    }
}