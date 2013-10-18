// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Kernel
// Description:  Basic structure of the system
//

#ifndef __KERNEL_STRUCTURES__
#define __KERNEL_STRUCTURES__

typedef signed char int8;           // size = 1
typedef signed short int16;         // size = 2
typedef signed int int32;           // size = 4
typedef signed long int int64;      // size = 8

typedef unsigned char uint8;        // size = 1
typedef unsigned short uint16;      // size = 2
typedef unsigned int uint32;        // size = 4
typedef unsigned long int uint64;   // size = 8

struct w_timer {
    uint32 usec;
    uint32 count;
    void (*func)(void);
    struct w_timer *next;
};
typedef struct w_timer w_timer_t;

#define WE_TRUE                 1
#define WE_FALSE                0

/* exit state */
#define WE_EXIT_FAILURE         1
#define WE_NULL                 0
#define WE_EXIT_SUCCESS         1

/* other */
#define WE_FULLSCREEN           1
#define WE_TEXT_SIZE            256

/* button state */
#define WE_STATE_DOWN           0
#define WE_STATE_UP             1
#define WE_LEFT_BUTTON          1
#define WE_MIDDLE_BUTTON        2
#define WE_RIGHT_BUTTON         3

#endif
