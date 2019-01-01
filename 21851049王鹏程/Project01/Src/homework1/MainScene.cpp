#include "MainScene.h"
#include "../Tools/ShaderLoader/LoadShaders.h"    // shader加载
#include <math.h>

#include "../Tools/TextureLoader/TextureLoader.h" // texture加载
#include "../Tools/ScreenShot/ScreenShot.h"       // 屏幕截图

#include <string>
#include "../System/System.h"					  // 系统功能

#define MAXTEXTURE	3													// 定义最大的纹理数目

// 在此处定义用户变量:
GLfloat	ep_Angle;														// 地球公转的角度
GLfloat	es_Angle;														// 地球自转的角度
GLfloat	mp_Angle;														// 月亮公转的角度
GLfloat	ms_Angle;														// 月亮自转的角度
GLuint	texture[MAXTEXTURE];											// 纹理数组，保存纹理名字
GLUquadricObj *quadric;													// 建立二次曲面对象

GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// 定义环境光的颜色
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// 定义漫反射光的颜色
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };					// 定义光源的位置

MainScene::MainScene()
{
	m_texLoader = NULL;
	m_screenShot = NULL;
}

MainScene::~MainScene()
{
	if ( NULL != m_texLoader) {
		m_texLoader = NULL;
	}
	if (NULL != m_screenShot) {
		m_screenShot = NULL;
	}
}

// 显示模式
void MainScene::ViewMode()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 透视模式
	// 此处width和height需要强制转化为float ： 因为GLWindow中将其定义为GLsizei，不强转可能拉遍opengl视口
	gluPerspective(45.0f, (float)this->GetWidth() / (float)this->GetHeight(), 0.01f, 100.0f);

	// 摄像机位置
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); 

	// 选择模式观察矩阵
	glMatrixMode(GL_MODELVIEW); 

	glLoadIdentity();
}

BOOL MainScene::initGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);

	// 选择深度测试方
	glDepthFunc(GL_LEQUAL);

	// 开启深度检测
	glEnable(GL_DEPTH_TEST);
	
	glShadeModel(GL_SMOOTH);

	// 最精细的透视计算
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 

	/////////////////////////////初始化////////////////////////////////////////
	
	// 加载纹理
	texture[0] = m_texLoader->LoadBitMapTexture("bitmap/earth.bmp");
	texture[1] = m_texLoader->LoadBitMapTexture("bitmap/sun.bmp");
	texture[2] = m_texLoader->LoadBitMapTexture("bitmap/moon.bmp");

	glEnable(GL_TEXTURE_2D);								// 开启2D纹理映射

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);			// 设置环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);			// 设置漫反射光

	quadric = gluNewQuadric();								// 建立一个曲面对象指针
	gluQuadricTexture(quadric, GLU_TRUE);					// 建立纹理坐标
	gluQuadricDrawStyle(quadric, GLU_FILL);					// 用面填充
	glEnable(GL_LIGHTING);									// 打开光照
	glEnable(GL_LIGHT1);									// 打开光源1
	
	//////////////////////////////////////////////////////////////////////////
	return TRUE;
}

BOOL MainScene::DrawGL(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // 清除颜色和深度缓存
	glLoadIdentity(); // 重置当前矩阵
	///////////////////////////////绘制////////////////////////////////////////
	
	glTranslatef(0.0f, 0.0f, -5.0f);						// 将坐标系移入屏幕8.0f
	glRotatef(10, 1.0f, 0.0f, 0.0f);						// 将坐标系绕x轴旋转10度
	glEnable(GL_LIGHT0);									// 打开光源0

/**********************************绘制太阳*************************************************/

	glBindTexture(GL_TEXTURE_2D, texture[1]);				// 绑定纹理
	
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);		// 设置光源1的当前位置
	glEnable(GL_TEXTURE_2D);

	gluSphere(quadric, 0.6f, 32, 32);						// 绘制太阳球体

/**********************************绘制地球*************************************************/

	glDisable(GL_LIGHT0);
	glRotatef(ep_Angle, 0.0f, 1.0f, 0.0f);					// 将坐标系绕Y轴旋转ep_Angle角度  控制地球公转
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);					// 将坐标系绕X轴旋转-90度

	glEnable(GL_TEXTURE_2D);								// 开启纹理

	glTranslatef(2.2f, 0.0f, 0.0f);							// 将坐标系右移2.0f
	glBindTexture(GL_TEXTURE_2D, texture[0]);				// 绑定纹理
	glPushMatrix();											// 当前模型视图矩阵入栈
	glRotatef(es_Angle, 0.0f, 0.0f, 1.0f);					// 将坐标系绕Z轴旋转es_Angle角度  控制地球自转
	gluSphere(quadric, 0.35f, 32, 32);						// 地球球体
	glPopMatrix();											// 当前模型视图矩阵出栈

/**********************************绘制月亮*************************************************/

	glRotatef(mp_Angle, 0.0f, 0.0f, 1.0f);					// 将坐标系绕Z轴旋转mp_Angle角度 控制月亮公转
	glBindTexture(GL_TEXTURE_2D, texture[2]);				// 绑定纹理
	glTranslatef(0.5f, 0.0f, 0.0f);							// 右移0.5f
	glRotatef(ms_Angle, 0.0f, 0.0f, 1.0f);					// 将坐标系绕Z轴旋转ms_Angle角度 控制月亮自转
	gluSphere(quadric, 0.1, 32, 32);						// 绘制月亮星体

/**********************************变量更新*************************************************/
	ep_Angle += 1.5f;  
	mp_Angle += 8.0f;
	es_Angle += 3.0f;
	ms_Angle += 7.0f;
	
	//////////////////////////////////////////////////////////////////////////

	glFlush(); // 刷新GL命令队列
	return TRUE;
}

BOOL MainScene::UpdateGL(GLvoid)
{
	/* 
	* 系统键盘映射说明
	* F1->F12     : VK_F1 -> VK_F12
	* num 0 -> 9  : VK_NUMPAD0 -> VK_NUMPAD9
	* char A -> Z : 0x41 -> ... 递增 
	*/

	if (keyDown(VK_F1))  // 按下F1 截屏并保存为bmp
	{
		m_screenShot->GrabScreen(this);
	}

	return TRUE;
}

GLvoid MainScene::DestroyGL(GLvoid)
{

}

