
#if !defined(MAINWND_H_INCLUDED)
#define MAINWND_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif
#include<vector>
using namespace std;

struct POINT3{
	double X;
	double Y;
	double Z;
};
struct WenLi{
	double TU;
	double TV;
};
struct FaXiangLiang{
	double NX;
	double NY;
	double NZ;
};
struct Mian{
	int V[3];
	int T[3];
	int N[3];	
};
class PIC
{
public:	
	vector<POINT3> V;
	vector<WenLi>  VT;
	vector<FaXiangLiang> VN;
	vector<Mian> F;
    
};

class CMainWnd  
{
public:
	CMainWnd();
	virtual ~CMainWnd();
	
	HWND m_hWnd;
	HGLRC m_hRC;
	GLfloat m_fAngle;
	PIC m_pic;

	void ReadPIC();
	void DrawScene();
	void KillScene();
	void InitScene();	
	void Tick(BOOL &bRedrawScene);
	void CMainWnd::GLCube();
};

#endif 
