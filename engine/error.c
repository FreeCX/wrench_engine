// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Error
// Last update:  29/01/13
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
    "Failed to register the Window class"
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
