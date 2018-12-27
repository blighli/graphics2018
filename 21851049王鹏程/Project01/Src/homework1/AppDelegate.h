#pragma once
#include "../GLWindow/QWndApp.h"

class AppDelegate : public QWndApp
{
public:
	AppDelegate();
	~AppDelegate();

public:

	// 初始化程序
	virtual BOOL InitInstance();

	// 退出程序
	virtual BOOL ExitInstance();
};