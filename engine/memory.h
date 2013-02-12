// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Memory
// Last update:  12/02/13
// Description:  Memory allocation system
//

#include <stdlib.h>
#include <stddef.h>
#include <malloc.h>
#include "structures.h"
#include "error.h"

/* export function */
void * weMalloc( size_t size );
void * weRealloc( void *ptr, size_t size );
void weFree( void *ptr );
size_t weMemoryUsage( void );
