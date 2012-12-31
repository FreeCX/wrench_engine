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

void * WE_malloc(size_t size);
void * WE_realloc(void *ptr, size_t size);
void WE_free(void *ptr);

size_t WE_MemoryUsage(void);
