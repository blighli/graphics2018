/*
*  author : 谭锦志
*  email  : apanoo@126.com
*  time   : 2014 07 20
*  ps     : 基于win32 API封装
*			支持win32标准控件完全自绘
*			支持opengl
*  参考    : MFC实现机制
*  use     : 方便编写windows下图形应用及插件
*/
#pragma once
#include "stdafx.h"

class QWnd
{
public:
	QWnd(void);
	virtual ~QWnd(void);  // 虚析构

public:
	BOOL CreateEx(DWORD dwExStyle,
		LPCTSTR lpClassName,
		LPCTSTR lpWindowName,
		DWORD dwStyle,
		int x,
		int y,
		int nWidth,
		int nHeight,
		QWnd* pWndParent,
		HMENU hMenu);

public:
	BOOL ShowWindow(int nShowCmd);
	BOOL UpdateWindow();
	BOOL DestroyWindow();

public:
	BOOL SubClassWindow(HWND hWnd);  // 子类化支持标准控件消息
	static QWnd* FromHandle(HWND hWnd);

	// virtual
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	virtual HRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);  // 真实的消息回调函数 - 虚函数，实现子类处理自己的消息
	HRESULT Default(UINT uMsg, WPARAM wParam, LPARAM lParam);  

public:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	HWND m_hWnd;
	WNDPROC m_lpfnOldWndProc;


	//////////////////////////////////////////////////////////////////////////////////////////////
	// 以下为其他消息封装，参考MFC的实现
public:// virtual message handler
	   // WM_ Message Handlers: A - C 
	virtual HRESULT OnActivate(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnActivateApp(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnAskCbFormatName(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnCancelMode(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnCaptureChanged(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnChangeCbChain(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnChar(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnCharToItem(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnChildActivate(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnClose(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnCompacting(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnCompareItem(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnContextMenu(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnCopyData(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnCreate(WPARAM wParam, LPARAM lParam);

	// WM_ Message Handlers: D - E 
	virtual HRESULT OnDeadChar(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnDeleteItem(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnDestroyClipboard(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnDevModeChange(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnDrawClipboard(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnDropFiles(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnEnable(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnEndSession(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnEnterIdle(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnEraseBkgnd(WPARAM wParam, LPARAM lParam);

	// WM_ Message Handlers: F - K
	virtual HRESULT OnFontChange(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnGetDlgCode(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnHelpInfo(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnHScroll(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnHScrollClipboard(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnIconEraseBkgnd(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnInitMenu(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnInitMenuPopup(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnKeyUp(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnKillFocus(WPARAM wParam, LPARAM lParam);

	//WM_ Message Handlers: L - M 
	virtual HRESULT OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMButtonDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMButtonUp(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMDIActivate(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMeasureItem(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMenuChar(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMenuSelect(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMouseActivate(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMove(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnMoving(WPARAM wParam, LPARAM lParam);

	//WM_ Message Handlers: N - O 
	virtual HRESULT OnNcActivate(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcCreate(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcDestroy(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcLButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcMButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcMButtonDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcMButtonUp(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcMouseMove(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcPaint(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcRButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcRButtonDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnNcRButtonUp(WPARAM wParam, LPARAM lParam);

	// WM_ Messages: P - R 
	virtual HRESULT OnPaint(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnPaintClipboard(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnPaletteChanged(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnPaletteIsChanging(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnParentNotify(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnQueryDragIcon(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnQueryEndSession(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnQueryNewPalette(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnQueryOpen(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnRButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnRButtonDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnRenderAllFormats(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnRenderFormat(WPARAM wParam, LPARAM lParam);

	// WM_ Messages: S 
	virtual HRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSetFocus(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnShowWindow(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSize(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSizeClipboard(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSizing(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSpoolerStatus(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnStyleChanged(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnStyleChanging(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSysChar(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSysColorChange(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSysCommand(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSysDeadChar(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSysKeyDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSysKeyUp(WPARAM wParam, LPARAM lParam);

	//WM_ Messages: T - Z 
	virtual HRESULT OnTCard(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnTimeChange(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnTimer(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnVKeyToItem(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnVScroll(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnVScrollClipboard(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnWindowPosChanged(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnWindowPosChanging(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnWinIniChange(WPARAM wParam, LPARAM lParam);
};
