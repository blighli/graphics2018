/* Copyright (c) 2009, �����׻������Ƽ����޹�˾
 * All Rights reserved.
 * �ļ����ƣ�Main App
 * �ļ���ʶ
 * ժҪ����������
 * ԭ���ߣ�Jeff Molofee ��2000��
 * ��лFredric Echols For Cleaning Up
 * ԭ������ַ��nehe.gamedev.net
 * ��۾������˵�һ�汾�޸ģ������˼��̿��ơ�
 * �����޸ģ������������������˲������˴���
 */

#include "StdAfx.h"
#include <math.h>
#include "VisionSimulation.h"

HDC			hDC=NULL;		// OpenGL��Ⱦ��������
HGLRC		hRC=NULL;		// ������ɫ��������
HWND		hWnd=NULL;		// �������ǵĴ��ھ��
HINSTANCE	hInstance;		// ��������ʵ��

BOOL	keys[256];			// ������̰���״̬������
BOOL	keyup[256];			// D
BOOL	active=TRUE;		// ���ڵĻ��־��ȱʡΪTRUE
BOOL	fullscreen=TRUE;	// ȫ��ȱʡ��־��ȱʡ�趨��ȫ��ģʽ

//VisionSimulation VStest;
GameScene * GStest;
double w_roll_speed; //����ת�٣��Ƕȣ�
double w_ori;//���ӷ���
void InitVisionSimulation();
void KeyControl();



LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// WndProc�Ķ���

///////////////////////////////////////////////////////////////////////////////
//
// ��������OpenGL�����Ĵ�С
//
//
///////////////////////////////////////////////////////////////////////////////
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// ��������OpenGL���ڴ�С
{
	if (height==0)										// ��ֹ�����
	{
		height=1;										// ǿ����1
	}
	
	glViewport(0,0,width,height);						// ���赱ǰ���ӿ�
	
	glMatrixMode(GL_PROJECTION);						// ѡ��ͶӰ����
	glLoadIdentity();									// ����ͶӰ����
	
	// ���㲢�����ӿڵĴ�С
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	
	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�͹۲����
	glLoadIdentity();									// ����ģ�͹۲����
}

///////////////////////////////////////////////////////////////////////////////
//
// ��ʼ��OpenGL �����������Ļ���õ���ɫ������Ȼ��棬������Ӱƽ����
//
//
///////////////////////////////////////////////////////////////////////////////

int InitGL(GLvoid)										// �˴���ʼ��OpenGL������������
{
	glEnable(GL_TEXTURE_2D);							// ��������ӳ��
	glShadeModel(GL_SMOOTH);							// ������Ӱƽ��
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// ����ɫΪ ��ɫ
	glClearDepth(1.0f);									// ������Ȼ���
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���
	glDepthFunc(GL_LEQUAL);								// ������Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// ����ϵͳ��͸�ӽ�������
	//////////////////////
	InitVisionSimulation();
	///////////////
	return TRUE;										// ���س�ʼ��OK��Ϣ
}

///////////////////////////////////////////////////////////////////////////////
//
//���������еĻ�ͼ����
//
//
///////////////////////////////////////////////////////////////////////////////

int DrawGLScene(GLvoid)									// �˹����а������еĻ��ƴ���
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �����Ļ����Ȼ���
	glLoadIdentity();									// ���õ�ǰ��ģ�͹۲����
/***************************/
	GStest->DrawGL();
	if (GStest->start==1)
		if (GStest->Cars->ready==1) 
			GStest->Cars->MovingCalc(&w_roll_speed,&w_ori,GStest->Cars);
	
/********************************/
	return TRUE;										// ���ػ�ͼ�ɹ���ɵ���Ϣ
}

///////////////////////////////////////////////////////////////////////////////
//���´���ֻ�ڳ����˳�ʱ���á������ͷ���ɫ�������豸������ʹ��ھ����
//���Ѽ�����Ӧ�Ĵ�����
//
//
///////////////////////////////////////////////////////////////////////////////
GLvoid KillGLWindow(GLvoid)								// �������ٴ���
{
	if (fullscreen)										// �Ƿ���ȫ��ģʽ?
	{
		ChangeDisplaySettings(NULL,0);					// �������ȫ��ģʽ��ص�����
		ShowCursor(TRUE);								// ��ʾ���ָ��
	}

	if (hRC)											// ����ӵ��OpenGL��Ⱦ������ô��
	{
		if (!wglMakeCurrent(NULL,NULL))					// �����ܷ��ͷ�DC��RC������?
		{
			MessageBox(NULL,"�ͷ�DC��RC������ʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// �ܷ�ɾ��RC?
		{
			MessageBox(NULL,"�ͷ�RCʧ��.","�رմ���",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// ����RCΪNULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// �ܷ��ͷ�DC?
	{
		MessageBox(NULL,"�ͷ�DCʧ��.","�رմ���",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// ���� DC Ϊ NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// �ܷ����ٴ���?
	{
		MessageBox(NULL,"���ٴ���ʧ��.","�رմ���",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// ���� hWnd Ϊ NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// �ܷ�ע���ࣿ
	{
		MessageBox(NULL,"����ע��������.","�رմ���",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// ���� hInstance Ϊ NULL
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���´��봴�����ǵ�OpenGL���ڣ��ṩ5������
// title -���ڵı�����
// width -���ڵĿ��
// height -���ڵĸ߶�
// bits    -ɫ��λ�� ��16/24/32��
// fullscreenflag  -ȫ��Ļ��־  TRUE -ȫ��ģʽ FALSE -����ģʽ
// ���ص�BOOLֵ��ʾ�����Ƿ�ɹ�����
/////////////////////////////////////////////////////////////////////////////// 
BOOL CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
	GLuint		PixelFormat;			// �������ƥ��Ľ��
	WNDCLASS	wc;						// ������ṹ
	DWORD		dwExStyle;				// ��չ���ڷ��
	DWORD		dwStyle;				// ���ڷ��
	RECT		WindowRect;				// ȡ�þ��ε����ϽǺ����½ǵ�����ֵ
	WindowRect.left=(long)0;			// ��Left��Ϊ0
	WindowRect.right=(long)width;		// ��Right��ΪҪ��Ŀ��
	WindowRect.top=(long)0;				// ��Top��Ϊ0
	WindowRect.bottom=(long)height;		// ��Bottom��ΪҪ��ĸ߶�

	fullscreen=fullscreenflag;			// ����ȫ��ȫ����־

	hInstance			= GetModuleHandle(NULL);				// ȡ�����Ǵ��ڵ�ʵ��
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// �ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc������Ϣ
	wc.cbClsExtra		= 0;									// �޶��ⴰ������
	wc.cbWndExtra		= 0;									// �޶��ⴰ������
	wc.hInstance		= hInstance;							// ����ʵ��
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// װ��ȱʡͼ��
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// װ�����ָ��
	wc.hbrBackground	= NULL;									// GL����Ҫ����
	wc.lpszMenuName		= NULL;									// ����Ҫ�˵�
	wc.lpszClassName	= "OpenGL";								// �趨������

	if (!RegisterClass(&wc))									// ����ע�ᴰ����
	{
		MessageBox(NULL,"ע�ᴰ����ʧ��","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// �˳�������FALSE
	}
	
	if (fullscreen)												// ����ȫ��ģʽ��?
	{
		DEVMODE dmScreenSettings;								// �豸ģʽ
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// ȷ���ڴ����Ϊ0
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Devmode�ṹ�Ĵ�С
		dmScreenSettings.dmPelsWidth	= width;				// ��ѡ��Ļ���
		dmScreenSettings.dmPelsHeight	= height;				// ��ѡ��Ļ�߶�
		dmScreenSettings.dmBitsPerPel	= bits;					// ÿ������ѡ��ɫ�����
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// ����������ʾģʽ�����ؽ������ע��CDS_FULLSCREEN��ȥ��״̬����
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// ��ģʽʧ�ܣ��ṩ����ѡ��˳��򴰿�������
			if (MessageBox(NULL,"ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��","�Ƿ�ʹ�ô���ģʽ��",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// ѡ�񴰿�ģʽ������ Fullscreen = FALSE
			}
			else
			{
				// ����һ���Ի��򣬸����û��������
				MessageBox(NULL,"���򽫱��ر�.","����",MB_OK|MB_ICONSTOP);
				return FALSE;									// �˳������� FALSE
			}
		}
	}

	if (fullscreen)												// �Դ���ȫ��ģʽô?
	{
		dwExStyle=WS_EX_APPWINDOW;								// ��չ������
		dwStyle=WS_POPUP;										// ������
		ShowCursor(FALSE);										// �������ָ��
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// ��չ������
		dwStyle=WS_OVERLAPPEDWINDOW;							// ������
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// �������ڴﵽ����Ҫ��Ĵ�С

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// ��չ������
								"OpenGL",							// ������
								title,								// ���ڱ���
								dwStyle |							// ѡ��Ĵ�������
								WS_CLIPSIBLINGS |					// ����Ĵ���������
								WS_CLIPCHILDREN,					// ����Ĵ���ָ�����
								0, 0,								// ����λ��
								WindowRect.right-WindowRect.left,	// ��������õĴ��ڿ��
								WindowRect.bottom-WindowRect.top,	// ��������õĴ��ڸ߶�
								NULL,								// �޸�����
								NULL,								// �޲˵�
								hInstance,							// ʵ��
								NULL)))								// ����WM_CREATE�����κ���Ϣ
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܴ���һ�������豸������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd ���ߴ���������ϣ�������飬������ʹ�õ����ظ�ʽ
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// ������ʽ�������Ĵ�С
		1,											// �汾��
		PFD_DRAW_TO_WINDOW |						// ��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |						// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,							// ����֧��˫����
		PFD_TYPE_RGBA,								// ����RGBAģʽ
		bits,										// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,							// ���Ե�ɫ��λ
		0,											// ��Alpha����
		0,											// ����Shift Bit
		0,											// ���ۼӻ���
		0, 0, 0, 0,									// ���Ծۼ�λ
		16,											// 16Bit Z���棨��Ȼ��棩  
		0,											// ���ɰ滺��
		0,											// �޸�������
		PFD_MAIN_PLANE,								// ����ͼ��
		0,											// Reserved
		0, 0, 0										// �����ڱ���
	};
	
	if (!(hDC=GetDC(hWnd)))							// ȡ���豸��������ô?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܴ���һ����ƥ������ظ�ʽ.","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Windows�ҵ���Ӧ�����ظ�ʽ��ô?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"�����������ظ�ʽ","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ����FASLE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// �Ƿ�����������ظ�ʽ?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"�޷��������ظ�ʽ","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// �ܷ�ȡ����ɫ������?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܴ���OpenGL��Ⱦ������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ����FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// ���Լ�����ɫ������
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܼ��ǰ��OpenGL��Ⱦ������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// ��ʾ����
	SetForegroundWindow(hWnd);						// ����������ȼ�
	SetFocus(hWnd);									// ���ü��̵Ľ������˴���
	ReSizeGLScene(width, height);					// ����͸��GL��Ļ

	if (!InitGL())									// ��ʼ���½���GL����
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"��ʼ��ʧ��","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ����FALSE
	}

	return TRUE;									// �ɹ�
}

///////////////////////////////////////////////////////////////////////////////
// �������еĴ�����Ϣ��������ע��ô�����֮�󣬳�����ת���ⲿ�Ŵ��봦������Ϣ
//
//
//
///////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(	HWND	hWnd,			// ���ڵľ��
							UINT	uMsg,			// ���ڵ���Ϣ
							WPARAM	wParam,			// ���ӵ���Ϣ����
							LPARAM	lParam)			// ���ӵ���Ϣ����
{
	switch (uMsg)									// ���Windows��Ϣ
	{
		case WM_ACTIVATE:							// ���Ӵ��ڼ�����Ϣ
		{
			if (!HIWORD(wParam))					// �����С��״̬
			{
				active=TRUE;						// ������ڼ���״̬
			}
			else
			{
				active=FALSE;						// ������ڷǼ���״̬
			}

			return 0;								// ������Ϣѭ��
		}

		case WM_SYSCOMMAND:							// ϵͳ�ж�����
		{
			switch (wParam)							// ���ϵͳ����
			{
				case SC_SCREENSAVE:					// ��Ļ����Ҫ����ô?
				case SC_MONITORPOWER:				// ��ʾ��Ҫ����ڵ�ģʽ?
				return 0;							// ��ֹ��������ķ���
			}
			break;									// �˳�
		}

		case WM_CLOSE:								// �յ��ر���Ϣ?
		{
			PostQuitMessage(0);						// ����һ���˳���Ϣ
			return 0;								// ����
		}

		case WM_KEYDOWN:							// �м�����ô?
		{
			keys[wParam] = TRUE;					// ����ǣ����ΪTRUE
			return 0;								// ����
		}

		case WM_KEYUP:								// �м��ſ�ô?
		{
			keys[wParam] = FALSE;					// ����ǣ����ΪFALSE
			return 0;								// ����
		}

		case WM_SIZE:								// ����OpenGL���ڴ�С
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// ����
		}
	}

	// ��DefWindowProc��������δ�������Ϣ��
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

///////////////////////////////////////////////////////////////////////////////
// Windows�������
// ���ô��ڴ�������,��������Ϣ,�������˻�����
//
//
//
///////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE	hInstance,			// ��ǰ����ʵ��
				   HINSTANCE	hPrevInstance,		// ǰһ������ʵ��
				   LPSTR		lpCmdLine,			// �����в���
				   int			nCmdShow)			// ������ʾ״̬
{
	MSG		msg;									// Windows��Ϣ�ṹ
	BOOL	done=FALSE;								// �����˳�ѭ����BOOL����
	
	// ��ʾ�û�ѡ������ģʽ
	if (MessageBox(NULL
		,"�Ƿ�Ҫ��ȫ����ʽ���г���?"
		, "����ȫ��ģʽ?"
		,MB_YESNO|MB_ICONQUESTION
		)==IDNO)
	{
		fullscreen=FALSE;							// ���ѡ�������ô���ģʽ
	}
	
	// ����OpenGL����
	if (!CreateGLWindow("�����Ӿ����濪�����",640,480,16,fullscreen))
	{
		return 0;									// �������ʧ�����˳�
	}
	
	while(!done)									// ����ѭ��ֱ�� done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// ����Ϣ�ڵȴ�ô?
		{
			if (msg.message==WM_QUIT)				// �Ƿ��յ��˳���Ϣ?
			{
				done=TRUE;							// ������� done=TRUE
			}
			else									// ������ǣ���������Ϣ
			{
				TranslateMessage(&msg);				// ������Ϣ
				DispatchMessage(&msg);				// ������Ϣ
			}
		}
		else										// ���û����Ϣ
		{
			// ���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ
			if (active)								// �����Ǽ����ô?
			{
				if (keys[VK_ESCAPE])				// ESC ������ô?
				{
					done=TRUE;						// ESC �����˳��ź�
				}
				else								// �����˳���ʱ��ˢ����Ļ
				{
					DrawGLScene();					// ���Ƴ���
					SwapBuffers(hDC);				// �������棨˫���棩
					KeyControl();					// ������̰���
				}
			}
			
			if (keys[VK_F1])						// F1��������ô?
			{
				keys[VK_F1]=FALSE;					// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪFALSE
				KillGLWindow();						// ���ٵ�ǰ�Ĵ���
				fullscreen=!fullscreen;				// �л� ȫ��/���� ģʽ
				// �ؽ�OpenGL����
				if (!CreateGLWindow("�����Ӿ����濪�����",640,480,16,fullscreen))
				{
					return 0;						// ����޷������������˳�����
				}
			}
		}
	}
	
	// �رճ���
	KillGLWindow();									// ���ٴ���
	return (msg.wParam);							// �˳�����
}

///////////////////////////////////////////////////////////////////////////////
// ��ʼ���Ӿ�����
// ���ô��ڴ�������,��������Ϣ,�������˻�����
//
//
//
///////////////////////////////////////////////////////////////////////////////

void InitVisionSimulation()
{
	
	GStest = new GameScene();
	GStest->Cars=new myCar();
	GStest->Cars->CreateDemoCar();
	GStest->start = 1;
	w_roll_speed = 0;
	w_ori = 0;
}




void KeyControl()
{
			////////////////-------------------------------
			if (keys[VK_UP] && keyup[VK_UP]) // UP ���Ѱ��²����ɿ���?
			{
				keyup[VK_UP]=false; // lp ��Ϊ TRUE
		//		StartM001->ChoiceUp();
			}
			if (!keys[VK_UP]) // UP���ɿ���ô?
			{
				keyup[VK_UP]=true; // ���ǣ���lp��ΪFALSE
			}
			////////////////--------------------------------------
			if (keys[VK_DOWN] && keyup[VK_DOWN]) // DOWN���Ѱ��²����ɿ���?
			{
				keyup[VK_DOWN]=false; // lp ��Ϊ TRUE
			//	StartM001->ChoiceDown();
			}
			if (!keys[VK_DOWN]) // DOWN���ɿ���ô?
			{
				keyup[VK_DOWN]=true; // ���ǣ���lp��ΪFALSE
			}
			////////////-------------------------------�س���
			if (keys[VK_RETURN] && keyup[VK_RETURN]) 
			{
				keyup[VK_RETURN]=false;
			//	if (StartM001->ChoiceON())
			//	{
		//			if (StartM001->_choice==0)
			//		{
			//		GStest->start = 1;
			//		}
			//	}
			}
			if (!keys[VK_RETURN]) 
			{
				keyup[VK_RETURN]=true;
			}
			//////////--------------------
			if (keys[VK_NUMPAD8]) 
			{
				if (GStest->start==1)
				{
					GStest->rotx += 1;
				}
			}
			//////////--------------------
			if (keys[VK_NUMPAD2] )
			{
				if (GStest->start==1)
				{
					GStest->rotx -= 1;
				}
			}
			//////////--------------------
			if (keys[VK_NUMPAD4]) 
			{
				if (GStest->start==1)
				{
					GStest->roty -= 1;
				}
			}
			//////////--------------------
			if (keys[VK_NUMPAD6])
			{
				if (GStest->start==1)
				{
					GStest->roty += 1;
				}
			}
			//////////--------------------
			if (keys[VK_NUMPAD7])
			{
				if (GStest->start==1)
				{
					GStest->rotz -= 1;
				}
			}
			//////////--------------------
			if (keys[VK_NUMPAD9])
			{
				if (GStest->start==1)
				{
					GStest->rotz += 1;
				}
			}
			//////////-------------------
			if (keys[VK_PRIOR])
			{
				GStest->deep-= 0.1f;
			}
			if (keys[VK_NEXT])
			{
				GStest->deep+= 0.1f;
			}
			////----------------------
			if (keys[VK_UP]) // Up�����������ô?
			{
				if (GStest->start==1)
				if (GStest->Cars->ready == 1)
				{
					if (w_roll_speed<0)
					{
						w_roll_speed += 0.1;
					}
					else if (w_roll_speed<5)
					{
						w_roll_speed += 0.3;
					}
					else if (w_roll_speed<10)
					{
						w_roll_speed += 0.7;
					}
					else if (w_roll_speed<20)
					{
						w_roll_speed += 1.2;
					}
					else if (w_roll_speed<30)
					{
						w_roll_speed += 1.4;
					}
					else if (w_roll_speed<50) 
					{
						w_roll_speed += 1.0;
					}

					if (w_roll_speed>50) w_roll_speed =50;
				}
			}
			if (keys[VK_DOWN]) // Down�����������ô?
			{
				if (GStest->start==1)
				if (GStest->Cars->ready == 1)
				{
					if (w_roll_speed>0)
					{
						w_roll_speed -= 3;
					}
					else if (w_roll_speed>-10)
					{
						w_roll_speed -= 0.5;
					}
					else if (w_roll_speed>-20)
					{
						w_roll_speed -= 1.3;
					}
					else if (w_roll_speed>-30)
					{
						w_roll_speed -= 1.2;
					}
					if (w_roll_speed<-40) w_roll_speed =  -40;
				}
			}
			if (keys[VK_RIGHT]) // Right�����������ô?
			{
				if (GStest->start==1)
				{
					if (GStest->Cars->ready == 1)
					{
						::w_ori -= 1.8;
						if (::w_ori<-50)
						{
							::w_ori=-50;
						}
					}
				}
			}
			if (keys[VK_LEFT]) // Left�����������ô?
			{
				if (GStest->start==1)
				{
					if (GStest->Cars->ready == 1)
					{	
						::w_ori += 1.8;
						if (::w_ori>50)
						{
							::w_ori=50;
						}
					}
				}
			}
			/////////------------------------------------V   �ӽ�  viewangle
			if (keys['V'] && keyup['V']) 
			{
				keyup['V']=false;
				if (GStest->start==1)
				{
					if (GStest->Cars->ready == 1)
					{
						if (GStest->Cars->viewangle ==0)
						{
							GStest->Cars->viewangle = 3;
						}
						else if (GStest->Cars->viewangle ==3)
						{
							GStest->Cars->viewangle = 0;
						}
					}
				}
			}
			if (!keys['V']) 
			{
				keyup['V']=true;
			}

}

