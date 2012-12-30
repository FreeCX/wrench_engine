// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Error
// Last update:  30/12/12
// Description:  Error handling system
//

#include "error.h"

static int last_error = 0;
static char str_error[] = "> ERROR: %s\n";

static char *str_error_msg[] = {
    "No error",
    "Can't allocate memory"
};

void WE_SendError(int error)
{
    last_error = error;
}

int WE_GetError(void)
{
    return last_error;
}

char ** WE_GetErrorString(void)
{
    return &str_error_msg[last_error];
}

void WE_PrintError(void)
{
    printf(str_error, str_error_msg[last_error]);
}
