// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Keymap
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
    #define WE_KEY_F1               XK_F1
    #define WE_KEY_F2               XK_F2
    #define WE_KEY_F3               XK_F3
    #define WE_KEY_F4               XK_F4
    #define WE_KEY_F5               XK_F5
    #define WE_KEY_F6               XK_F6
    #define WE_KEY_F7               XK_F7
    #define WE_KEY_F8               XK_F8
    #define WE_KEY_F9               XK_F9
    #define WE_KEY_F10              XK_F10
    #define WE_KEY_F11              XK_F11
    #define WE_KEY_F12              XK_F12
    #define WE_KEY_PRINT            XK_Print
    
    #define WE_KEY_TAB              XK_Tab
    #define WE_KEY_ESCAPE           XK_Escape
    #define WE_KEY_SPACE            XK_Space
    #define WE_KEY_INSERT           XK_Insert
//    #define WE_KEY_LWIN             0x0000
//    #define WE_KEY_RWIN             0x0000
//    #define WE_KEY_MENU             0x000087
    #define WE_KEY_PAUSE            XK_Pause
    #define WE_KEY_BACKSPACE        XK_BackSpace
    #define WE_KEY_ENTER            XK_Return
    #define WE_KEY_RSHIFT           XK_Shift_R
    #define WE_KEY_LSHIFT           XK_Shift_L
    #define WE_KEY_RCTRL            XK_Control_R
    #define WE_KEY_LCTRL            XK_Control_L
    #define WE_KEY_RALT             XK_Alt_R
    #define WE_KEY_LALT             XK_Alt_L

    #define WE_KEY_CAPSLOCK         XK_Caps_Lock
    #define WE_KEY_SCROLLLOCK       XK_Scroll_Lock
    #define WE_KEY_NUMLOCK          XK_Num_Lock

    #define WE_KEY_PAGEUP           XK_Page_Up
    #define WE_KEY_PAGEDOWN         XK_Page_Down
    #define WE_KEY_END              XK_End
    #define WE_KEY_HOME             XK_Home
    #define WE_KEY_LEFT             XK_Left
    #define WE_KEY_UP               XK_Up
    #define WE_KEY_RIGHT            XK_Right
    #define WE_KEY_DOWN             XK_Down
    #define WE_KEY_DELETE           XK_Delete
#endif

#endif