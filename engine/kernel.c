// 
//    Programm:  Wrench Engine
//        Type:  Source Code
//      Module:  Kernel
// Last update:  29/12/12
// Description:  The core of the system
//

#include "kernel.h"

static char *engine_name = "Wrench Engine";
static char *engine_date = "29/12/12";

static int major_version = 0;
static int minor_version = 1;
static int build_version = 0;

int __DEBUG__ = 0;

int WE_Init(int argc, char **argv)
{
    /* insert code */
}

#ifdef __WIN32__
void WE_Info(void)
{
    char buffer[256];
    int dwBuild, i;

    int dwVersion = GetVersion();
    int dwMajor = (LOBYTE(LOWORD(dwVersion)));
    int dwMinor = (HIBYTE(LOWORD(dwVersion)));

    if (dwVersion < 0x80000000) {
		dwBuild = (DWORD)(HIWORD(dwVersion));
		sprintf(buffer, "Windows [Version %d.%d.%d]", 
            dwMajor, dwMinor, dwBuild);
	}
	else if (dwMajor < 4){
		dwBuild = (DWORD)(HIWORD(dwVersion) & ~0x8000); 
		sprintf(buffer, "WIN32s [Version %d.%d.%d]", 
            dwMajor, dwMinor, dwBuild);
	} 
	else {
		dwBuild = 0;
		sprintf(buffer, "Win95/Win98 [Version %d.%d.%d]", 
            dwMajor, dwMinor, dwBuild);
	}

    printf("%s %d.%d.%d [%s]\n", engine_name, major_version, 
        minor_version, build_version, engine_date);
    printf("Working at %s\n", buffer);
}
#elif __LINUX__
void WE_Info(void)
{
    struct utsname _system;

    printf("%s %d.%d.%d [%s]\n", engine_name, major_version, 
        minor_version, build_version, engine_date);
    if (!uname(&_system))
        printf("Working at %s %s %s\n", _system.sysname, 
            _system.release, _system.machine);
}
#endif

void WE_About(char **name, int *major_v, int *minor_v)
{
    *name = engine_name;
    major_v = major_version;
    minor_v = minor_version;
}
