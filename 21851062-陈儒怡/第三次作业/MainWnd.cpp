
#include "stdafx.h"
#include "MainWnd.h"
#include <sstream>
#include <fstream>
using namespace std;


CMainWnd::CMainWnd():
m_hWnd(NULL),
m_fAngle(0.0f),
m_hRC(NULL)
{

}

CMainWnd::~CMainWnd()
{
}


#define YU 1
void CMainWnd::GLCube()
{
	for(int i=0;i<m_pic.F.size();i++)
	{
		glBegin(GL_TRIANGLES);
		if(m_pic.VT.size()!=0)glTexCoord2f(m_pic.VT[m_pic.F[i].T[0]].TU,m_pic.VT[m_pic.F[i].T[0]].TV);
		if(m_pic.VN.size()!=0)glNormal3f(m_pic.VN[m_pic.F[i].N[0]].NX,m_pic.VN[m_pic.F[i].N[0]].NY,m_pic.VN[m_pic.F[i].N[0]].NZ);
		glVertex3f(m_pic.V[m_pic.F[i].V[0]].X/YU,m_pic.V[m_pic.F[i].V[0]].Y/YU, m_pic.V[m_pic.F[i].V[0]].Z/YU);

		if(m_pic.VT.size()!=0)glTexCoord2f(m_pic.VT[m_pic.F[i].T[1]].TU,m_pic.VT[m_pic.F[i].T[1]].TV);
		if(m_pic.VN.size()!=0)glNormal3f(m_pic.VN[m_pic.F[i].N[1]].NX,m_pic.VN[m_pic.F[i].N[1]].NY,m_pic.VN[m_pic.F[i].N[1]].NZ);
		glVertex3f(m_pic.V[m_pic.F[i].V[1]].X/YU,m_pic.V[m_pic.F[i].V[1]].Y/YU, m_pic.V[m_pic.F[i].V[1]].Z/YU);

		if(m_pic.VT.size()!=0)glTexCoord2f(m_pic.VT[m_pic.F[i].T[2]].TU,m_pic.VT[m_pic.F[i].T[2]].TV);
		if(m_pic.VN.size()!=0)glNormal3f(m_pic.VN[m_pic.F[i].N[2]].NX,m_pic.VN[m_pic.F[i].N[2]].NY,m_pic.VN[m_pic.F[i].N[2]].NZ);
		glVertex3f(m_pic.V[m_pic.F[i].V[2]].X/YU,m_pic.V[m_pic.F[i].V[2]].Y/YU, m_pic.V[m_pic.F[i].V[2]].Z/YU);
		glEnd();
	}		
}


void CMainWnd::InitScene()
{
	ReadPIC();
	glClearColor(0.000f, 0.000f, 0.000f, 1.0f);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	 glEnable(GL_TEXTURE_2D);

	static GLfloat glfMatAmbient[] = {0.000f, 0.450f, 1.000f, 1.0f};
	static GLfloat glfMatDiffuse[] = {0.000f, 0.000f, 0.580f, 1.0f};
	static GLfloat glfMatSpecular[]= {1.000f, 1.000f, 1.000f, 1.0f};
	static GLfloat glfMatEmission[]= {0.000f, 0.000f, 0.000f, 1.0f};
	static GLfloat fShininess = 128.000f;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT,  glfMatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,  glfMatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, glfMatSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, glfMatEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, fShininess);
}


void CMainWnd::KillScene()
{
	
}


void CMainWnd::DrawScene()
{
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	GLfloat glfLight[] = {-4.0f, 4.0f, 4.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, glfLight);
	
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fAngle, 0.0f, 1.0f, 0.0f);
	
	
	GLCube();
	
	glFlush();
}


void CMainWnd::Tick(BOOL &bRedrawScene)
{
	m_fAngle+= 0.1;
}

void CMainWnd::ReadPIC()
{
	ifstream ifs("cube.obj");//cube 
	string s;
	Mian *f;
	POINT3 *v;
	FaXiangLiang *vn;
	WenLi	*vt;
	while(getline(ifs,s))
	{
		if(s.length()<2)continue;
		if(s[0]=='v'){
			if(s[1]=='t'){
				istringstream in(s);
				vt=new WenLi();
				string head;
				in>>head>>vt->TU>>vt->TV;
				m_pic.VT.push_back(*vt);
			}else if(s[1]=='n'){
				istringstream in(s);
				vn=new FaXiangLiang();
				string head;
				in>>head>>vn->NX>>vn->NY>>vn->NZ;
				m_pic.VN.push_back(*vn);
			}else{
				istringstream in(s);
				v=new POINT3();
				string head;
				in>>head>>v->X>>v->Y>>v->Z;
				m_pic.V.push_back(*v);
			}
		}
		else if(s[0]=='f'){
			for(int k=s.size()-1;k>=0;k--){
				if(s[k]=='/')s[k]=' ';
			}
			istringstream in(s);
			f=new Mian();
			string head;
			in>>head;
			int i=0;
			while(i<3)
			{
				if(m_pic.V.size()!=0)
				{
					in>>f->V[i];
					f->V[i]-=1;
				}
				if(m_pic.VT.size()!=0)
				{
					in>>f->T[i];
					f->T[i]-=1;
				}
				if(m_pic.VN.size()!=0)
				{
					in>>f->N[i];
					f->N[i]-=1;
				}
				i++;
			}
			m_pic.F.push_back(*f);
		}
	}
}
