// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Error
// Last update:  11/02/13
// Description:  Error handling system
//

#include "error.h"

static int last_error = 0;
static char str_error[] = "> ERROR: %s\n";

static char *str_error_msg[] = {
    "No error",
    "Can't allocate memory",
    
    "Release of DC and RC failed",
    "Release Rendering Context Failed",
    "Failed to register the Window class",
    "Window creation error",
    "Couldn't create GL device context",
    "Couldn't find suitable PixelFormat",
    "Couldn't set PixelFormat",
    "Couldn't create GL rendering context",
    "Couldn't ativate GL rendering context",

    "Couldn't release drawing context",
    "Couldn't open display",
    "X Server no support GLX Extension",
    "GLX 1.3 or greater necessary"
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
