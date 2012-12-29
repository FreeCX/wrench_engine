// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Error
// Last update:  29/12/12
// Description:  Error handling system
//

#ifndef __KERNEL_ERROR__
#define __KERNEL_ERROR__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    WE_ERROR_NONE,
    WE_ERROR_ALLOC_MEMORY
};

/* export function */

void WE_SendError(int error);
int WE_GetError(void);
char ** WE_GetErrorString(void);
void WE_PrintError(void);

#endif
