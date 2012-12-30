// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Memory
// Last update:  30/12/12
// Description:  Memory allocation system
//

#include <stdlib.h>
#include <stddef.h>
#include <malloc.h>

#include "structures.h"
#include "error.h"

/* export function */

void * WE_Malloc(size_t size);
void * WE_Realloc(void *ptr, size_t size);
void WE_Free(void *ptr);

size_t WE_MemoryUsage(void);
