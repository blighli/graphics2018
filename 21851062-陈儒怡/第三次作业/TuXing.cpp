
#include "stdafx.h"
#include "TuXing.h"


CApp gApp;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!gApp.InitInstance(hInstance, nCmdShow, lpCmdLine)) 
		return FALSE;

	int nRet = gApp.Run();

	gApp.ExitInstance();

	return nRet;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	return gApp.WindowProc(hWnd, message, wParam, lParam);
}

CApp::CApp():
	m_hInst(0),
	m_pMainWnd(NULL)	
{
}

CApp::~CApp()
{
}


BOOL CApp::InitInstance(HINSTANCE hInstance, int nCmdShow, LPSTR lpCmdLine)
{
	const char szWindowClass[] = "TuXingWindowClass";
	const char szWindowTitle[] = "TuXing";

	m_hInst = hInstance;

	
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUXING);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = 0;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	if(!RegisterClassEx(&wcex))
		return FALSE;

	
	m_pMainWnd = new CMainWnd;
	m_pMainWnd->m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, szWindowClass, szWindowTitle, 
		WS_OVERLAPPED | WS_THICKFRAME | WS_CAPTION |WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	
	if (!m_pMainWnd->m_hWnd)
	{
		delete m_pMainWnd;
		return FALSE;
	}
	OnCreate();

	
	ShowWindow(m_pMainWnd->m_hWnd, nCmdShow);
	UpdateWindow(m_pMainWnd->m_hWnd);

	return TRUE;
}


void CApp::ExitInstance()
{
}


BOOL CApp::OnCommand(int nCmdID, int nEvent)
{
	switch (nCmdID)
	{				
		case IDM_EXIT:
			SendMessage(m_pMainWnd->m_hWnd, WM_CLOSE, 0, 0);
			break;
		default:
			return FALSE;
	}
	return TRUE;
}


int CApp::Run()
{  
	MSG msg;
	while(TRUE)
  {
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
    {
      if(!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
    }
    else
      OnIdle();
	}

	delete m_pMainWnd;
	m_pMainWnd = NULL;

	return msg.wParam;
}


LRESULT CApp::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;

	switch (message) 
	{
		case WM_CLOSE:
			DestroyWindow(m_pMainWnd->m_hWnd);
			m_pMainWnd->m_hWnd = 0;
			break;
		case WM_COMMAND:
			if(!OnCommand(LOWORD(wParam), HIWORD(wParam)))
				return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);
			OnPaint(hDC);
			EndPaint(hWnd, &ps);
			break;
		case WM_CREATE:
			break;
		case WM_DESTROY:
			OnDestroy();
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			OnSize(LOWORD(lParam), HIWORD(lParam));
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}


void CApp::OnIdle()
{
	BOOL bRedraw = TRUE;
	m_pMainWnd->Tick(bRedraw);
	if(bRedraw)
	{
		HDC hDC = GetDC(m_pMainWnd->m_hWnd);
		if(hDC)
		{
			wglMakeCurrent(hDC, m_pMainWnd->m_hRC);
			m_pMainWnd->DrawScene(); 
			SwapBuffers(hDC);
			wglMakeCurrent(0, 0);
		}
		ReleaseDC(m_pMainWnd->m_hWnd, hDC);
	}
}


void CApp::OnCreate()
{
	
	PIXELFORMATDESCRIPTOR pfd;
	int nPixelFormat;	
	memset(&pfd, NULL, sizeof(pfd));    
  pfd.nSize      = sizeof(pfd);
  pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
	
	
	HDC hDC = GetDC(m_pMainWnd->m_hWnd);
  nPixelFormat = ChoosePixelFormat(hDC, &pfd);
  SetPixelFormat(hDC, nPixelFormat, &pfd);
	
	
	m_pMainWnd->m_hRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, m_pMainWnd->m_hRC);
	  
	m_pMainWnd->InitScene();
  wglMakeCurrent(0, 0);

	
	ReleaseDC(m_pMainWnd->m_hWnd, hDC);

	
	RECT rc;
	GetClientRect(m_pMainWnd->m_hWnd, &rc);
	OnSize(rc.right-rc.left, rc.bottom-rc.top);
}


void CApp::OnDestroy()
{
	HDC hDC = GetDC(m_pMainWnd->m_hWnd);
	wglMakeCurrent(hDC, m_pMainWnd->m_hRC);
	m_pMainWnd->KillScene();
  wglMakeCurrent(0, 0);
	wglDeleteContext(m_pMainWnd->m_hRC);
	ReleaseDC(m_pMainWnd->m_hWnd, hDC);
}


void CApp::OnSize(int cx, int cy)
{
	if(cx==0 || cy ==0 || m_pMainWnd->m_hWnd==NULL)
		return;

	GLfloat fFovy  = 30.0f;
  GLfloat fZNear = 1.0f;
  GLfloat fZFar = 10.0f;  

	HDC hDC = GetDC(m_pMainWnd->m_hWnd);
	wglMakeCurrent(hDC, m_pMainWnd->m_hRC);
	
	
	RECT rv;
	GetClientRect(m_pMainWnd->m_hWnd, &rv);
	GLfloat fAspect = (GLfloat)(rv.right-rv.left) / (GLfloat)(rv.bottom-rv.top);

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fFovy, fAspect, fZNear, fZFar);
	glViewport(rv.left, rv.top, rv.right-rv.left, rv.bottom-rv.top);
	glMatrixMode(GL_MODELVIEW);

	wglMakeCurrent(0, 0);
	ReleaseDC(m_pMainWnd->m_hWnd, hDC);
}


void CApp::OnPaint(HDC hDC)
{
	wglMakeCurrent(hDC, m_pMainWnd->m_hRC);
	m_pMainWnd->DrawScene();
	SwapBuffers(hDC);
	wglMakeCurrent(0, 0);
}
