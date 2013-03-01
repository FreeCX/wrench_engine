// 
//    Programm:  Wrench Engine
//        Type:  Header
//      Module:  Keymap
// Last update:  28/02/13
// Description:  Keyboard map
//

#ifndef __KERNEL_KEYMAP__
#define __KERNEL_KEYMAP__

#ifdef __WIN32__
	#define WE_KEY_BACKSPACE		0x000008
	#define WE_KEY_
#else __linux__
	#define WE_KEY_ESCAPE			0x000009
	#define WE_KEY_
#endif

#endif