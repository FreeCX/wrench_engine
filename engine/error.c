// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Error
// Last update:  19/01/13
// Description:  Error handling system
//

#include "error.h"

static int last_error = 0;
static char str_error[] = "> ERROR: %s\n";

static char *str_error_msg[] = {
    "No error",
    "Can't allocate memory"
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
