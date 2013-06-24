// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Memory
// Description:  Memory allocation system
//

#include <stdlib.h>
#include <stddef.h>
#include <malloc.h>
#include "structures.h"
#include "error.h"

/* export function */
void * weMalloc( size_t size );
void * weCalloc( size_t nmemb, size_t size );
void * weRealloc( void *ptr, size_t size );
void weFree( void *ptr );
size_t weMemoryUsage( void );
