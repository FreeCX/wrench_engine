// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Memory
// Description:  Memory allocation system
//

#include "memory.h"

static size_t alloc_memory = 0;
extern int __DEBUG_FLAG__;

void * weMalloc( size_t size )
{
    void *ptr = NULL;

    ptr = malloc( size );
    if ( __DEBUG_FLAG__ ) {
#ifdef __WIN32__
        printf( "  [>] address of pointer 0x%p\n", ptr );
#elif __linux__
        printf( "  [>] address of pointer %p\n", ptr );
#endif
        printf( "  [+] allocating %lu bytes\n", (unsigned long) size );
    }
    if ( ptr == NULL ) {
        weSendError( WE_ERROR_ALLOC_MEMORY );
        exit( WE_EXIT_FAILURE );
    }
    alloc_memory += size;
    return ptr;
}

void * weCalloc( size_t nmemb, size_t size )
{
    void *ptr = NULL;

    ptr = calloc( nmemb, size );
    if ( __DEBUG_FLAG__ ) {
#ifdef __WIN32__
        printf( "  [>] address of pointer 0x%p\n", ptr );
#elif __linux__
        printf( "  [>] address of pointer %p\n", ptr );
#endif
        printf( "  [+] allocating %lu bytes\n", (unsigned long) size );
    }
    if ( ptr == NULL ) {
        weSendError( WE_ERROR_ALLOC_MEMORY );
        exit( WE_EXIT_FAILURE );
    }
    alloc_memory += size;
    return ptr;
}

void * weRealloc( void *ptr, size_t size )
{
    void *buf = NULL;

#ifdef __WIN32__
    alloc_memory -= _msize( ptr );
#elif __linux__
    alloc_memory -= malloc_usable_size( ptr );
#endif
    buf = realloc( ptr, size );
    if ( __DEBUG_FLAG__ ) {
#ifdef __WIN32
        printf( "  [>] address of pointer 0x%p\n", buf );
#else
        printf( "  [>] address of pointer %p\n", buf );
#endif
        printf( "  [+] reallocating %lu bytes\n", (unsigned long) size );
    }
    if ( ptr == NULL ) {
        weSendError( WE_ERROR_ALLOC_MEMORY );
        exit( WE_EXIT_FAILURE );
    }
    alloc_memory += size;
    return buf;
}

void weFree( void *ptr )
{
#ifdef __WIN32__
    alloc_memory -= _msize( ptr );
#elif __linux__
    alloc_memory -= malloc_usable_size( ptr );
#endif
    if ( __DEBUG_FLAG__ ) {
#ifdef __WIN32__
        printf( "  [-] free %lu bytes at 0x%p\n", (unsigned long) _msize( ptr ), ptr );
#elif __linux__
        printf( "  [-] free %lu bytes at %p\n", (unsigned long) malloc_usable_size( ptr ), ptr );
#endif
    }
    free( ptr );
}

size_t weMemoryUsage( void )
{
    return alloc_memory;
}
