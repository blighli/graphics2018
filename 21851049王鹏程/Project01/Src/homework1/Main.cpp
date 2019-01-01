/************************************************************************/
/* time   : 2015-12-02                                                  */
/* author : 谭锦志                                                       */
/* email  : apanoo@126.com                                              */
/************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include "Main.h"
#include "AppDelegate.h"

// link to libraries
// #pragma comment(lib, "opengl32.lib")
// #pragma comment(lib, "glu32.lib")
// #pragma comment(lib, "winmm.lib")

// WinMain 入口函数

AppDelegate theApp;  // 全局变量

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
						HINSTANCE	hPrevInstance,		// Previous Instance
						LPSTR		lpCmdLine,			// Command line params
						int			nShowCmd)			// Window show state
{
	theApp.InitInstance();  
	theApp.run();		    
	theApp.ExitInstance();

	return true;
}
