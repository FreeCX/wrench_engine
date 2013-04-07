// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Keymap
// Last update:  07/04/13
// Description:  Keyboard map
//

#ifndef __KERNEL_KEYMAP__
#define __KERNEL_KEYMAP__

#ifdef __WIN32__
    #define WE_KEY_F1               0x000070
    #define WE_KEY_F2               0x000071
    #define WE_KEY_F3               0x000072
    #define WE_KEY_F4               0x000073
    #define WE_KEY_F5               0x000074
    #define WE_KEY_F6               0x000075
    #define WE_KEY_F7               0x000076
    #define WE_KEY_F8               0x000077
    #define WE_KEY_F9               0x000078
    #define WE_KEY_F10              0x000079
    #define WE_KEY_F11              0x00007A
    #define WE_KEY_F12              0x00007C
    #define WE_KEY_PRINT            0x00002C
    
    #define WE_KEY_TAB              0x000009
    #define WE_KEY_ESCAPE           0x00001B
    #define WE_KEY_SPACE            0x000020
    #define WE_KEY_INSERT           0x00002D
    #define WE_KEY_LWIN             0x00005B
    #define WE_KEY_RWIN             0x00005C
    #define WE_KEY_MENU             0x00005D
    #define WE_KEY_PAUSE            0x000013
    #define WE_KEY_BACKSPACE        0x000008
    #define WE_KEY_ENTER            0x00000D
    #define WE_KEY_RSHIFT           0x000010
    #define WE_KEY_LSHIFT           0x000010
    #define WE_KEY_RCTRL            0x000011
    #define WE_KEY_LCTRL            0x000012
//    #define WE_KEY_RALT             0x0000
//    #define WE_KEY_LALT             0x0000

    #define WE_KEY_CAPSLOCK         0x000014
    #define WE_KEY_SCROLLLOCK       0x000091
    #define WE_KEY_NUMLOCK          0x000090

    #define WE_KEY_PAGEUP           0x000021
    #define WE_KEY_PAGEDOWN         0x000022
    #define WE_KEY_END              0x000023
    #define WE_KEY_HOME             0x000024
    #define WE_KEY_LEFT             0x000025
    #define WE_KEY_UP               0x000026
    #define WE_KEY_RIGHT            0x000027
    #define WE_KEY_DOWN             0x000028
    #define WE_KEY_DELETE           0x00002E
#elif __linux__
    #define WE_KEY_F1               0x000043
    #define WE_KEY_F2               0x000044
    #define WE_KEY_F3               0x000045
    #define WE_KEY_F4               0x000046
    #define WE_KEY_F5               0x000047
    #define WE_KEY_F6               0x000048
    #define WE_KEY_F7               0x000049
    #define WE_KEY_F8               0x00004A
    #define WE_KEY_F9               0x00004B
    #define WE_KEY_F10              0x00004C
    #define WE_KEY_F11              0x00005F
    #define WE_KEY_F12              0x000060
    #define WE_KEY_PRINT            0x00006B
    
    #define WE_KEY_TAB              0x000017
    #define WE_KEY_ESCAPE           0x000009
    #define WE_KEY_SPACE            0x000041
    #define WE_KEY_INSERT           0x000076
//    #define WE_KEY_LWIN             0x0000
//    #define WE_KEY_RWIN             0x0000
    #define WE_KEY_MENU             0x000087
    #define WE_KEY_PAUSE            0x00007F
    #define WE_KEY_BACKSPACE        0x000016
    #define WE_KEY_ENTER            0x000024
    #define WE_KEY_RSHIFT           0x00003E
    #define WE_KEY_LSHIFT           0x000032
    #define WE_KEY_RCTRL            0x000069
    #define WE_KEY_LCTRL            0x000025
    #define WE_KEY_RALT             0x000040
    #define WE_KEY_LALT             0x00006C

//    #define WE_KEY_CAPSLOCK         0x0000
//    #define WE_KEY_SCROLLLOCK       0x0000
//    #define WE_KEY_NUMLOCK          0x0000

    #define WE_KEY_PAGEUP           0x000070
    #define WE_KEY_PAGEDOWN         0x000075
    #define WE_KEY_END              0x000073
    #define WE_KEY_HOME             0x00006E
    #define WE_KEY_LEFT             0x000071
    #define WE_KEY_UP               0x00006F
    #define WE_KEY_RIGHT            0x000072
    #define WE_KEY_DOWN             0x000074
    #define WE_KEY_DELETE           0x000077
#endif

#endif