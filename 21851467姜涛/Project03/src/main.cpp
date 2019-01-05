#include "pch.h"
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <string>

using namespace std;
bool ReadASCII(const char *buffer);
bool ReadBinary(const char *buffer);

struct Point3D
{
	float x;
	float y;
	float z;
};
struct Face {
	Point3D vector;
	Point3D xpoint;
	Point3D ypoint;
	Point3D zpoint;
};
vector<Face>faceList;
bool mouseLeftDown=false;
bool mouseRightDown=false;
bool mouseMiddleDown;
float mouseX=0.0f, mouseY=0.0f;
float cameraDistanceX=0.0f;
float cameraDistanceY=0.0f;
float cameraAngleX=0.0f;
float cameraAngleY=0.0f;
float times = 1.0f;
int count_=0;

bool ReadFile()   //文件读取
{
	FILE * pFile;
	long lSize;
	char* buffer;
	size_t result;
	pFile = fopen("E:\\model\\v1.stl","rb");
	if (pFile == NULL)
	{
		fputs("File NULL", stderr);
		exit(1);
	}
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	buffer = (char*)malloc(sizeof(char)*lSize);
	stringstream ss(buffer);
	
	if (buffer == NULL)
	{
		fputs("Memory error", stderr);
		exit(2);
	}
	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		fputs("Reading error", stderr);
		exit(3);
	}
	fclose(pFile);
	ReadBinary(buffer);
	string temp;
	ss >> temp;
	if (temp == "solid")//判断格式
	{
		ReadASCII(buffer);
	}
	else
	{
		ReadBinary(buffer);
	}

	free(buffer);
	return true;
}

bool ReadASCII(const char *buffer) //读取文本格式STL文件
{
	Point3D vec,point[3];
	int i;
	string name, useless;
	Face temp;
	stringstream ss(buffer);
	ss >> name >> name;
	ss.get();
	do {
		ss >> useless;
		if (useless != "facet")
			break;
		ss >> useless;
		ss >> vec.x >> vec.y >> vec.z;	
		ss.get();
		getline(ss, useless);
		//ss.get();
		for (i = 0; i < 3; i++)
		{
			ss >> useless >> point[i].x >> point[i].y >> point[i].z;
			ss.get();
			
		}
		temp.vector = vec;
		temp.xpoint = point[0];
		temp.ypoint = point[1];
		temp.zpoint = point[2];
		faceList.push_back(temp);
		count_++;
		getline(ss, useless);
		getline(ss, useless);
	} while (1);
	cout << count_++;
	for (int i = 0; i < 1; ++i)
	{
		cout << faceList[i].vector.x << '	' << faceList[i].vector.y << '	' << faceList[i].vector.z << endl;
		cout << faceList[i].xpoint.x << '	' << faceList[i].xpoint.y << '	' << faceList[i].xpoint.z << endl;
		cout << faceList[i].ypoint.x << '	' << faceList[i].ypoint.y << '	' << faceList[i].ypoint.z << endl;
		cout << faceList[i].zpoint.x << '	' << faceList[i].zpoint.y << '	' << faceList[i].zpoint.z << endl;
		cout << endl;
	}
	return true;
}
bool ReadBinary(const char *buffer)    //读取二进制格式STL文件
{
	const char* p = buffer;
	Face temp;
	char name[80];
	int i, j;
	memcpy(name, p, 80);
	p += 80;
	memcpy((char*)&count_, p, 4);
	p += 4;
	for (i = 0; i < count_; i++)
	{
		Point3D point[4];
		for (j = 0; j < 4; j++)//读取三顶点
		{
			memcpy((char*)&(point[j].x), p, 4);
			memcpy((char*)&(point[j].y), p+4, 4);
			memcpy((char*)&(point[j].z), p+8, 4);
			p += 12;
		}
		temp.vector = point[0];
		temp.xpoint = point[1];
		temp.ypoint = point[2];
		temp.zpoint = point[3];
		faceList.push_back(temp);
		p += 2;//跳过尾部标志
	}
	for (int i = 0;i<5 ; ++i)
	{
		cout << faceList[i].vector.x << '	' << faceList[i].vector.y << '	' << faceList[i].vector.z << endl;
		cout << faceList[i].xpoint.x << '	' << faceList[i].xpoint.y << '	' << faceList[i].xpoint.z << endl;
		cout << faceList[i].ypoint.x << '	' << faceList[i].ypoint.y << '	' << faceList[i].ypoint.z << endl;
		cout << faceList[i].zpoint.x << '	' << faceList[i].zpoint.y << '	' << faceList[i].zpoint.z << endl;
		cout << endl;
	}
	
	cout << count_;
	return true;
}
GLuint list = 1;
void init()  
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_COLOR_MATERIAL);
	
	GLfloat qaAmbientLight[] = {1.0, 1.0, 1.0, 1.0 };
	GLfloat qaDiffuseLight[] = { 1.0, 1.0, 1.0, 1 };
	GLfloat qaSpecularLight[] = { 1, 1, 1, 1.0 };
	GLfloat qaLightPosition[] = { 0, 0, 50, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);    //设置光源1
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);	
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	

	GLfloat qaAmbientLight1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat qaDiffuseLight1[] = { 1.0, 1.0, 1.0, 1 };
	GLfloat qaSpecularLight1[] = { 1, 1, 1, 1.0 };
	GLfloat qaLightPosition1[] = { 50, 0, 50, 1 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight1); // 设置光源2
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60);
	
	GLfloat ma_abient[] = { 0.1,0,0,1 };
	GLfloat ma_diffuse[] = { 0.1,0,0,1 };
	GLfloat ma_specular[] = { 1.0,1.0,1.0,1 };
	GLfloat shinness[] = { 40 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ma_abient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ma_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ma_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shinness);
	GLfloat mat_ambient[] = { 1,1,1,1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, mat_ambient);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	int a = count_ / 20000;             //使用显示列表
	auto it2 = faceList.begin();
	for (int i = 0; i <=a; ++i)
	{
		
			glNewList(list + i, GL_COMPILE);
			glBegin(GL_TRIANGLES);
			for (int j=0; it2 != faceList.end()&&j<20000; it2++,++j)
			{
				glNormal3f(it2->vector.x, it2->vector.y, it2->vector.z);
				glVertex3f((it2->xpoint).x, (it2->xpoint).y, (it2->xpoint.z));
				glVertex3f((it2->ypoint).x, (it2->ypoint.y), (it2->ypoint.z));
				glVertex3f((it2->zpoint).x, (it2->zpoint).y, (it2->zpoint).z);
			}
			glEnd();
			glEndList();
	
	}
	
	
}
void mouseCB(int button, int state, int x, int y)   //判断鼠标状态
{
	mouseX = x;
	mouseY = y;
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			
			mouseLeftDown = true;

		}
		else if (state == GLUT_UP)
			mouseLeftDown = false;
	}

	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if (state == GLUT_UP)
			mouseRightDown = false;
	}
	else if (state == GLUT_UP && button == 3)
	{
		times *= 1.2;
	}

	else if (state == GLUT_UP && button == 4)
	{
		times *= 0.8;
	}
	glutPostRedisplay();
}
void mouseMotionCB(int x, int y)   //鼠标控制物体旋转、平移、旋转
{

	if (mouseLeftDown)
	{
		cameraAngleY += (x - mouseX);
		cameraAngleX += (y - mouseY);
		mouseX = x;
		mouseY = y;

	}
	if (mouseRightDown)
	{
		cameraDistanceX = (x - mouseX)*2;
		cameraDistanceY = (y - mouseY)*2;
		mouseY = y;
		mouseX = x;
	}

	glutPostRedisplay();
}
float lx = 0.0f,lz=-1.0f,angle=0.0f;
float x = 0.0f, z = 10.0f;

void inputkey(int key, int x, int y)  //键盘方向键控制视点进行场景漫游
{
	switch (key) {
	case GLUT_KEY_LEFT:angle -= 0.01f; lx = sin(angle); lz = -cos(angle); break;
	case GLUT_KEY_RIGHT:angle += 0.01f; lx = sin(angle); lz = -cos(angle); break;
	case GLUT_KEY_DOWN: x -= lx * 0.1;z-=lz*0.1; break;
	case GLUT_KEY_UP: x += lx * 0.1; z += lz * 0.1; break;
	}
	glutPostRedisplay();
}
void display()   //绘制物体
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glPushMatrix();

	gluLookAt(x, 0, z, x+lx,0, z+lz, 0, 1, 0);
	//glPopMatrix();
	glScalef(times, times, times);//缩放
	glTranslatef(cameraDistanceX, cameraDistanceY, 0);
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);
	for (int i = 0; i < (count_ / 20000 + 1); ++i)
		glCallList(list + i);
	//glutSolidTeapot(3.0);
	glutSwapBuffers();
	//glFlush();

}

void reshape(GLsizei w, GLsizei h)
{


	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0, (GLdouble)w / (GLdouble)h, 1.0, 40.0);
	gluPerspective(60.0, (double)w / h, 1.0, 1000); 
	glMatrixMode(GL_MODELVIEW);
	
}

int main(int argc, char* argv[])
{
	ReadFile();
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("复杂模型显示");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);
	glutSpecialFunc(inputkey);
	glutMainLoop();
	return 0;
}

