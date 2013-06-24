// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Kernel
// Description:  Basic structure of the system
//

#ifndef __KERNEL_STRUCTURES__
#define __KERNEL_STRUCTURES__

#ifdef __WIN32__
    typedef unsigned __int64 uint;
#endif

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
