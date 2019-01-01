#include "AppDelegate.h"
#include "MainScene.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

BOOL AppDelegate::InitInstance()
{
	MainScene *pMainWnd = new MainScene();
	if (NULL == pMainWnd)
	{
		return 0; // 窗口创建失败
	}
	m_pMainWnd = (LPVOID)pMainWnd;  // 保留引用

	pMainWnd->CreateGlWnd("ogl-framework", 200, 100, 800, 600); 
	pMainWnd->ShowWindow(SW_SHOW);
	pMainWnd->UpdateWindow();

	return TRUE;
}

BOOL AppDelegate::ExitInstance()
{
	if (m_pMainWnd)
	{
		delete m_pMainWnd;  // 退出前处理
		m_pMainWnd = NULL;
	}
	return true;
}

