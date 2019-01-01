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
#include "QWnd.h"

QWnd::QWnd(void)
{
	m_hWnd = NULL;
	m_lpfnOldWndProc = NULL;
}

QWnd::~QWnd(void)
{

}

// 注意：WndProc将回调转交给WindowProc虚成员函数
LRESULT CALLBACK QWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCCREATE == uMsg) // 捕获漏掉的WM_NVCREATE消息
	{
		CREATESTRUCT* pCs = (CREATESTRUCT*)lParam;
		if (pCs)
		{
			QWnd* pWnd = (QWnd*)pCs->lpCreateParams;
			if (pWnd)
			{
				pWnd->m_hWnd = hWnd;
				pWnd->m_lpfnOldWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC); // 取出关联的m_hWnd
				return pWnd->OnNcCreate(wParam, lParam);
			}
		}
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	if (WM_CREATE == uMsg) // 捕获漏掉的WM_CREATE消息
	{
		CREATESTRUCT* pCs = (CREATESTRUCT*)lParam;
		if (pCs)
		{
			QWnd* pWnd = (QWnd*)pCs->lpCreateParams;
			if (pWnd)
			{
				pWnd->m_hWnd = hWnd;
				pWnd->m_lpfnOldWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);  // 创建好后将m_hWnd关联起来
				return pWnd->OnCreate(wParam, lParam);
			}
		}
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	QWnd* pWnd = (QWnd*)GetWindowLong(hWnd, GWL_USERDATA);
	if (pWnd)
	{
		return pWnd->WindowProc(uMsg, wParam, lParam);
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// 注册窗口类
BOOL QWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	BOOL bRet = GetClassInfoEx(cs.hInstance, cs.lpszClass, &wcex);
	if (bRet)
	{
		return TRUE;
	}

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = QWnd::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = cs.hInstance;
	wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);
	wcex.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);

	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = cs.lpszClass;
	return ::RegisterClassEx(&wcex);
}

// 创建窗口
BOOL QWnd::CreateEx(DWORD dwExStyle,
	LPCTSTR lpClassName,
	LPCTSTR lpWindowName,
	DWORD dwStyle,
	int x,
	int y,
	int nWidth,
	int nHeight,
	QWnd* pWndParent,
	HMENU hMenu)
{
	assert(!IsWindow(m_hWnd));

	HWND hWndParent = NULL;
	if (pWndParent)
	{
		hWndParent = pWndParent->m_hWnd;
	}

	CREATESTRUCT cs;
	cs.lpCreateParams = this;
	cs.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	cs.hMenu = hMenu;
	cs.hwndParent = hWndParent;
	cs.cx = nWidth;
	cs.cy = nHeight;
	cs.y = y;
	cs.x = x;
	cs.style = dwStyle;
	cs.lpszName = lpWindowName;
	cs.lpszClass = lpClassName;
	cs.dwExStyle = dwExStyle;

	BOOL bRet = PreCreateWindow(cs);
	assert(bRet);

	HWND hWnd = CreateWindowEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style,
		cs.x, cs.y, cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);
	if (NULL == hWnd) return FALSE;

	m_hWnd = hWnd;
	SetWindowLong(m_hWnd, GWL_USERDATA, (long)this);
	m_lpfnOldWndProc = (WNDPROC)GetWindowLong(m_hWnd, GWL_WNDPROC);

	if (m_lpfnOldWndProc != QWnd::WndProc)
	{
		SetWindowLong(m_hWnd, GWL_WNDPROC, (long)QWnd::WndProc);
	}

	return TRUE;
}

HRESULT QWnd::Default(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_lpfnOldWndProc == WndProc)
	{
		return ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	return m_lpfnOldWndProc(m_hWnd, uMsg, wParam, lParam);
}

BOOL QWnd::ShowWindow(int nShowCmd)
{
	assert(IsWindow(m_hWnd));
	::ShowWindow(m_hWnd, nShowCmd);
	::SetForegroundWindow(m_hWnd);  // 提升窗口优先级，避免被其他窗口挡住
	::SetFocus(m_hWnd);
	return TRUE;
}

BOOL QWnd::UpdateWindow()
{
	assert(IsWindow(m_hWnd));
	return ::UpdateWindow(m_hWnd);
}

BOOL QWnd::DestroyWindow()
{
	assert(IsWindow(m_hWnd));
	return ::DestroyWindow(m_hWnd);
}

// 处理子类化，支持标准控件消息
BOOL QWnd::SubClassWindow(HWND hWnd)
{
	assert(IsWindow(hWnd));
	if (m_hWnd == hWnd) return TRUE;

	m_lpfnOldWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);
	if (WndProc != m_lpfnOldWndProc)
	{
		m_hWnd = hWnd;
		SetWindowLong(m_hWnd, GWL_USERDATA, (long)this);
		SetWindowLong(m_hWnd, GWL_WNDPROC, (long)WndProc);
		return TRUE;
	}
	return FALSE;
}

QWnd* QWnd::FromHandle(HWND hWnd)
{
	assert(IsWindow(hWnd));
	QWnd* pWnd = (QWnd*)GetWindowLong(hWnd, GWL_USERDATA);
	return pWnd;
}


	//////////////////////////////////////////////////////////////////////////////////////////////
	// 以下为其他消息封装，参考MFC的实现
HRESULT QWnd::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		return OnActivate(wParam, lParam);
	case WM_ACTIVATEAPP:
		return OnActivateApp(wParam, lParam);
	case WM_ASKCBFORMATNAME:
		return OnAskCbFormatName(wParam, lParam);
	case WM_CANCELMODE:
		return OnCancelMode(wParam, lParam);
	case WM_CAPTURECHANGED:
		return OnCaptureChanged(wParam, lParam);
	case WM_CHANGECBCHAIN:
		return OnChangeCbChain(wParam, lParam);
	case WM_CHAR:
		return OnChar(wParam, lParam);
	case WM_CHARTOITEM:
		return OnCharToItem(wParam, lParam);
	case WM_CHILDACTIVATE:
		return OnChildActivate(wParam, lParam);
	case WM_CLOSE:
		return OnClose(wParam, lParam);
	case WM_COMPACTING:
		return OnCompacting(wParam, lParam);
	case WM_COMPAREITEM:
		return OnCompareItem(wParam, lParam);
	case WM_CONTEXTMENU:
		return OnContextMenu(wParam, lParam);
	case WM_COPYDATA:
		return OnCopyData(wParam, lParam);
	case WM_CREATE:
		return OnCreate(wParam, lParam);

	case WM_DEADCHAR:
		return OnDeadChar(wParam, lParam);
	case WM_DELETEITEM:
		return OnDeleteItem(wParam, lParam);
	case WM_DESTROY:
		return OnDestroy(wParam, lParam);
	case WM_DESTROYCLIPBOARD:
		return OnDestroyClipboard(wParam, lParam);
	case WM_DEVICECHANGE:
		return OnDeviceChange(wParam, lParam);
	case WM_DEVMODECHANGE:
		return OnDevModeChange(wParam, lParam);
	case WM_DRAWCLIPBOARD:
		return OnDrawClipboard(wParam, lParam);
	case WM_DRAWITEM:
		return OnDrawItem(wParam, lParam);
	case WM_DROPFILES:
		return OnDropFiles(wParam, lParam);
	case WM_ENABLE:
		return OnEnable(wParam, lParam);
	case WM_ENDSESSION:
		return OnEndSession(wParam, lParam);
	case WM_ENTERIDLE:
		return OnEnterIdle(wParam, lParam);
	case WM_ERASEBKGND:
		return OnEraseBkgnd(wParam, lParam);

	case WM_FONTCHANGE:
		return OnFontChange(wParam, lParam);
	case WM_GETDLGCODE:
		return OnGetDlgCode(wParam, lParam);
	case WM_GETMINMAXINFO:
		return OnGetMinMaxInfo(wParam, lParam);
	case WM_HELP:
		return OnHelpInfo(wParam, lParam);
	case WM_HSCROLL:
		return OnHScroll(wParam, lParam);
	case WM_HSCROLLCLIPBOARD:
		return OnHScrollClipboard(wParam, lParam);
	case WM_ICONERASEBKGND:
		return OnIconEraseBkgnd(wParam, lParam);
	case WM_INITMENU:
		return OnInitMenu(wParam, lParam);
	case WM_INITMENUPOPUP:
		return OnInitMenuPopup(wParam, lParam);
	case WM_KEYDOWN:
		return OnKeyDown(wParam, lParam);
	case WM_KEYUP:
		return OnKeyUp(wParam, lParam);
	case WM_KILLFOCUS:
		return OnKillFocus(wParam, lParam);

	case WM_LBUTTONDBLCLK:
		return OnLButtonDblClk(wParam, lParam);
	case WM_LBUTTONDOWN:
		return OnLButtonDown(wParam, lParam);
	case WM_LBUTTONUP:
		return OnLButtonUp(wParam, lParam);
	case WM_MBUTTONDBLCLK:
		return OnMButtonDblClk(wParam, lParam);
	case WM_MBUTTONDOWN:
		return OnMButtonDown(wParam, lParam);
	case WM_MBUTTONUP:
		return OnMButtonUp(wParam, lParam);
	case WM_MDIACTIVATE:
		return OnMDIActivate(wParam, lParam);
	case WM_MEASUREITEM:
		return OnMeasureItem(wParam, lParam);
	case WM_MENUCHAR:
		return OnMenuChar(wParam, lParam);
	case WM_MENUSELECT:
		return OnMenuSelect(wParam, lParam);
	case WM_MOUSEACTIVATE:
		return OnMouseActivate(wParam, lParam);
	case WM_MOUSEMOVE:
		return OnMouseMove(wParam, lParam);
	case WM_MOUSEWHEEL:
		return OnMouseWheel(wParam, lParam);
	case WM_MOVE:
		return OnMove(wParam, lParam);
	case WM_MOVING:
		return OnMoving(wParam, lParam);

	case WM_NCACTIVATE:
		return OnNcActivate(wParam, lParam);
	case WM_NCCALCSIZE:
		return OnNcCalcSize(wParam, lParam);
	case WM_NCCREATE:
		return OnNcCreate(wParam, lParam);
	case WM_NCDESTROY:
		return OnNcDestroy(wParam, lParam);
	case WM_NCHITTEST:
		return OnNcHitTest(wParam, lParam);
	case WM_NCLBUTTONDBLCLK:
		return OnNcLButtonDblClk(wParam, lParam);
	case WM_NCLBUTTONDOWN:
		return OnNcLButtonDown(wParam, lParam);
	case WM_NCLBUTTONUP:
		return OnNcLButtonUp(wParam, lParam);
	case WM_NCMBUTTONDBLCLK:
		return OnNcMButtonDblClk(wParam, lParam);
	case WM_NCMBUTTONDOWN:
		return OnNcMButtonDown(wParam, lParam);
	case WM_NCMBUTTONUP:
		return OnNcMButtonUp(wParam, lParam);
	case WM_NCMOUSEMOVE:
		return OnNcMouseMove(wParam, lParam);
	case WM_NCPAINT:
		return OnNcPaint(wParam, lParam);
	case WM_NCRBUTTONDBLCLK:
		return OnNcRButtonDblClk(wParam, lParam);
	case WM_NCRBUTTONDOWN:
		return OnNcRButtonDown(wParam, lParam);
	case WM_NCRBUTTONUP:
		return OnNcRButtonUp(wParam, lParam);

	case WM_PAINT:
		return OnPaint(wParam, lParam);
	case WM_PAINTCLIPBOARD:
		return OnPaintClipboard(wParam, lParam);
	case WM_PALETTECHANGED:
		return OnPaletteChanged(wParam, lParam);
	case WM_PALETTEISCHANGING:
		return OnPaletteIsChanging(wParam, lParam);
	case WM_PARENTNOTIFY:
		return OnParentNotify(wParam, lParam);
	case WM_QUERYDRAGICON:
		return OnQueryDragIcon(wParam, lParam);
	case WM_QUERYENDSESSION:
		return OnQueryEndSession(wParam, lParam);
	case WM_QUERYNEWPALETTE:
		return OnQueryNewPalette(wParam, lParam);
	case WM_QUERYOPEN:
		return OnQueryOpen(wParam, lParam);
	case WM_RBUTTONDBLCLK:
		return OnNcRButtonDblClk(wParam, lParam);
	case WM_RBUTTONDOWN:
		return OnRButtonDown(wParam, lParam);
	case WM_RBUTTONUP:
		return OnRButtonUp(wParam, lParam);
	case WM_RENDERALLFORMATS:
		return OnRenderAllFormats(wParam, lParam);
	case WM_RENDERFORMAT:
		return OnRenderFormat(wParam, lParam);

	case WM_SETCURSOR:
		return OnSetCursor(wParam, lParam);
	case WM_SETFOCUS:
		return OnSetFocus(wParam, lParam);
	case WM_SHOWWINDOW:
		return OnShowWindow(wParam, lParam);
	case WM_SIZE:
		return OnSize(wParam, lParam);
	case WM_SIZECLIPBOARD:
		return OnSizeClipboard(wParam, lParam);
	case WM_SIZING:
		return OnSizing(wParam, lParam);
	case WM_SPOOLERSTATUS:
		return OnSpoolerStatus(wParam, lParam);
	case WM_STYLECHANGED:
		return OnStyleChanged(wParam, lParam);
	case WM_STYLECHANGING:
		return OnStyleChanging(wParam, lParam);
	case WM_SYSCHAR:
		return OnSysChar(wParam, lParam);
	case WM_SYSCOLORCHANGE:
		return OnSysColorChange(wParam, lParam);
	case WM_SYSCOMMAND:
		return OnSysCommand(wParam, lParam);
	case WM_SYSDEADCHAR:
		return OnSysDeadChar(wParam, lParam);
	case WM_SYSKEYDOWN:
		return OnSysKeyDown(wParam, lParam);
	case WM_SYSKEYUP:
		return OnSysKeyUp(wParam, lParam);

	case WM_TCARD:
		return OnTCard(wParam, lParam);
	case WM_TIMECHANGE:
		return OnTimeChange(wParam, lParam);
	case WM_TIMER:
		return OnTimer(wParam, lParam);
	case WM_VKEYTOITEM:
		return OnVKeyToItem(wParam, lParam);
	case WM_VSCROLL:
		return OnVScroll(wParam, lParam);
	case WM_VSCROLLCLIPBOARD:
		return OnVScrollClipboard(wParam, lParam);
	case WM_WINDOWPOSCHANGED:
		return OnWindowPosChanged(wParam, lParam);
	case WM_WINDOWPOSCHANGING:
		return OnWindowPosChanging(wParam, lParam);
	case WM_WININICHANGE:
		return OnWinIniChange(wParam, lParam);

	default:
		break;
	}
	return Default(uMsg, wParam, lParam);
}


// WM_ Message Handlers: A - C 
HRESULT QWnd::OnActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ACTIVATE, wParam, lParam);
}

HRESULT QWnd::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ACTIVATEAPP, wParam, lParam);
}

HRESULT QWnd::OnAskCbFormatName(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ASKCBFORMATNAME, wParam, lParam);
}

HRESULT QWnd::OnCancelMode(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CANCELMODE, wParam, lParam);
}

HRESULT QWnd::OnCaptureChanged(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CAPTURECHANGED, wParam, lParam);
}

HRESULT QWnd::OnChangeCbChain(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CHANGECBCHAIN, wParam, lParam);
}

HRESULT QWnd::OnChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CHAR, wParam, lParam);
}

HRESULT QWnd::OnCharToItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CHARTOITEM, wParam, lParam);
}

HRESULT QWnd::OnChildActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CHILDACTIVATE, wParam, lParam);
}

HRESULT QWnd::OnClose(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CLOSE, wParam, lParam);
}

HRESULT QWnd::OnCompacting(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_COMPACTING, wParam, lParam);
}

HRESULT QWnd::OnCompareItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_COMPAREITEM, wParam, lParam);
}

HRESULT QWnd::OnContextMenu(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CONTEXTMENU, wParam, lParam);
}

HRESULT QWnd::OnCopyData(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_COPYDATA, wParam, lParam);
}

HRESULT QWnd::OnCreate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CREATE, wParam, lParam);
}

// WM_ Message Handlers: D - E 
HRESULT QWnd::OnDeadChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DEADCHAR, wParam, lParam);
}

HRESULT QWnd::OnDeleteItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DELETEITEM, wParam, lParam);
}

HRESULT QWnd::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DESTROY, wParam, lParam);
}

HRESULT QWnd::OnDestroyClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DESTROYCLIPBOARD, wParam, lParam);
}

HRESULT QWnd::OnDeviceChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DEVICECHANGE, wParam, lParam);
}

HRESULT QWnd::OnDevModeChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DEVMODECHANGE, wParam, lParam);
}

HRESULT QWnd::OnDrawClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DRAWCLIPBOARD, wParam, lParam);
}

HRESULT QWnd::OnDrawItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DRAWITEM, wParam, lParam);
}

HRESULT QWnd::OnDropFiles(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DROPFILES, wParam, lParam);
}

HRESULT QWnd::OnEnable(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ENABLE, wParam, lParam);
}

HRESULT QWnd::OnEndSession(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ENDSESSION, wParam, lParam);
}

HRESULT QWnd::OnEnterIdle(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ENTERIDLE, wParam, lParam);
}

HRESULT QWnd::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ERASEBKGND, wParam, lParam);
}

// WM_ Message Handlers: F - K
HRESULT QWnd::OnFontChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_FONTCHANGE, wParam, lParam);
}

HRESULT QWnd::OnGetDlgCode(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_GETDLGCODE, wParam, lParam);
}

HRESULT QWnd::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_GETMINMAXINFO, wParam, lParam);
}

HRESULT QWnd::OnHelpInfo(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_HELP, wParam, lParam);
}

HRESULT QWnd::OnHScroll(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_HSCROLL, wParam, lParam);
}

HRESULT QWnd::OnHScrollClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_HSCROLLCLIPBOARD, wParam, lParam);
}

HRESULT QWnd::OnIconEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ICONERASEBKGND, wParam, lParam);
}

HRESULT QWnd::OnInitMenu(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_INITMENU, wParam, lParam);
}

HRESULT QWnd::OnInitMenuPopup(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_INITMENUPOPUP, wParam, lParam);
}

HRESULT QWnd::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_KEYDOWN, wParam, lParam);
}

HRESULT QWnd::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_KEYUP, wParam, lParam);
}

HRESULT QWnd::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_KILLFOCUS, wParam, lParam);
}

//WM_ Message Handlers: L - M 
HRESULT QWnd::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_LBUTTONDBLCLK, wParam, lParam);
}

HRESULT QWnd::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_LBUTTONDOWN, wParam, lParam);
}

HRESULT QWnd::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_LBUTTONUP, wParam, lParam);
}

HRESULT QWnd::OnMButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MBUTTONDBLCLK, wParam, lParam);
}

HRESULT QWnd::OnMButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MBUTTONDOWN, wParam, lParam);
}

HRESULT QWnd::OnMButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MBUTTONUP, wParam, lParam);
}

HRESULT QWnd::OnMDIActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MDIACTIVATE, wParam, lParam);
}

HRESULT QWnd::OnMeasureItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MEASUREITEM, wParam, lParam);
}

HRESULT QWnd::OnMenuChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MENUCHAR, wParam, lParam);
}

HRESULT QWnd::OnMenuSelect(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MENUSELECT, wParam, lParam);
}

HRESULT QWnd::OnMouseActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOUSEACTIVATE, wParam, lParam);
}

HRESULT QWnd::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOUSEMOVE, wParam, lParam);
}

HRESULT QWnd::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOUSEWHEEL, wParam, lParam);
}

HRESULT QWnd::OnMove(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOVE, wParam, lParam);
}

HRESULT QWnd::OnMoving(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOVING, wParam, lParam);
}

//WM_ Message Handlers: N - O 
HRESULT QWnd::OnNcActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCACTIVATE, wParam, lParam);
}

HRESULT QWnd::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCCALCSIZE, wParam, lParam);
}

HRESULT QWnd::OnNcCreate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCCREATE, wParam, lParam);
}

HRESULT QWnd::OnNcDestroy(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCDESTROY, wParam, lParam);
}

HRESULT QWnd::OnNcHitTest(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCHITTEST, wParam, lParam);
}

HRESULT QWnd::OnNcLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCLBUTTONDBLCLK, wParam, lParam);
}

HRESULT QWnd::OnNcLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCLBUTTONDOWN, wParam, lParam);
}

HRESULT QWnd::OnNcLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCLBUTTONUP, wParam, lParam);
}

HRESULT QWnd::OnNcMButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCRBUTTONDBLCLK, wParam, lParam);
}

HRESULT QWnd::OnNcMButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCMBUTTONDOWN, wParam, lParam);
}

HRESULT QWnd::OnNcMButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCMBUTTONUP, wParam, lParam);
}

HRESULT QWnd::OnNcMouseMove(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCMOUSEMOVE, wParam, lParam);
}

HRESULT QWnd::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCPAINT, wParam, lParam);
}

HRESULT QWnd::OnNcRButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCRBUTTONDBLCLK, wParam, lParam);
}

HRESULT QWnd::OnNcRButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCRBUTTONDOWN, wParam, lParam);
}

HRESULT QWnd::OnNcRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCRBUTTONUP, wParam, lParam);
}

// WM_ Messages: P - R 
HRESULT QWnd::OnPaint(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PAINT, wParam, lParam);
}

HRESULT QWnd::OnPaintClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PAINTCLIPBOARD, wParam, lParam);
}

HRESULT QWnd::OnPaletteChanged(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PALETTECHANGED, wParam, lParam);
}

HRESULT QWnd::OnPaletteIsChanging(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PALETTEISCHANGING, wParam, lParam);
}

HRESULT QWnd::OnParentNotify(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PARENTNOTIFY, wParam, lParam);
}

HRESULT QWnd::OnQueryDragIcon(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_QUERYDRAGICON, wParam, lParam);
}

HRESULT QWnd::OnQueryEndSession(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_QUERYENDSESSION, wParam, lParam);
}

HRESULT QWnd::OnQueryNewPalette(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_QUERYNEWPALETTE, wParam, lParam);
}

HRESULT QWnd::OnQueryOpen(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_QUERYOPEN, wParam, lParam);
}

HRESULT QWnd::OnRButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RBUTTONDBLCLK, wParam, lParam);
}

HRESULT QWnd::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RBUTTONDOWN, wParam, lParam);
}

HRESULT QWnd::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RBUTTONUP, wParam, lParam);
}

HRESULT QWnd::OnRenderAllFormats(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RENDERALLFORMATS, wParam, lParam);
}

HRESULT QWnd::OnRenderFormat(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RENDERFORMAT, wParam, lParam);
}


// WM_ Messages: S 
HRESULT QWnd::OnSetCursor(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SETCURSOR, wParam, lParam);
}

HRESULT QWnd::OnSetFocus(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SETFOCUS, wParam, lParam);
}

HRESULT QWnd::OnShowWindow(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SHOWWINDOW, wParam, lParam);
}

HRESULT QWnd::OnSize(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SIZE, wParam, lParam);
}

HRESULT QWnd::OnSizeClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SIZECLIPBOARD, wParam, lParam);
}

HRESULT QWnd::OnSizing(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SIZING, wParam, lParam);
}

HRESULT QWnd::OnSpoolerStatus(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SPOOLERSTATUS, wParam, lParam);
}

HRESULT QWnd::OnStyleChanged(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_STYLECHANGED, wParam, lParam);
}

HRESULT QWnd::OnStyleChanging(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_STYLECHANGING, wParam, lParam);
}

HRESULT QWnd::OnSysChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSCHAR, wParam, lParam);
}

HRESULT QWnd::OnSysColorChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSCOLORCHANGE, wParam, lParam);
}

HRESULT QWnd::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSCOMMAND, wParam, lParam);
}

HRESULT QWnd::OnSysDeadChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DEADCHAR, wParam, lParam);
}

HRESULT QWnd::OnSysKeyDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSKEYDOWN, wParam, lParam);
}

HRESULT QWnd::OnSysKeyUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSKEYUP, wParam, lParam);
}

//WM_ Messages: T - Z 
HRESULT QWnd::OnTCard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_TCARD, wParam, lParam);
}

HRESULT QWnd::OnTimeChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_TIMECHANGE, wParam, lParam);
}

HRESULT QWnd::OnTimer(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_TIMECHANGE, wParam, lParam);
}

HRESULT QWnd::OnVKeyToItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_VKEYTOITEM, wParam, lParam);
}

HRESULT QWnd::OnVScroll(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_VSCROLL, wParam, lParam);
}

HRESULT QWnd::OnVScrollClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_VSCROLLCLIPBOARD, wParam, lParam);
}

HRESULT QWnd::OnWindowPosChanged(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_WINDOWPOSCHANGED, wParam, lParam);
}

HRESULT QWnd::OnWindowPosChanging(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_WINDOWPOSCHANGING, wParam, lParam);
}

HRESULT QWnd::OnWinIniChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_WININICHANGE, wParam, lParam);
}