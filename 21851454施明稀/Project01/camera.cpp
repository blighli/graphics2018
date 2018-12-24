//WASDZC  控制相机上下左右前后移动

//P       切换投影方式（正投影与透视投影）
 
//O       切换渲染方式（填充模式与线框模式）
 
//空格键  启动与暂停旋转（桌子与茶壶一起绕桌子中心轴旋转）
 
//IKJL    控制茶壶前后左右移动。
 
//E       茶壶旋转
 
//Q       退出
 
 
#include <stdlib.h>
#include <GL/glut.h>
 
float fRotate    = 0.0f; //旋转因子（茶壶和桌子）
float fScale     = 1.0f; //缩放因子
 
float tRotate = 0.0f; //旋转因子（茶壶）
 
bool bPersp = false; //是否为透视投影 （vs 正投影）
bool bAnim = false; // 茶壶和桌子是否旋转
bool bWire = false; // 绘制模式是否为线形 （vs 填充）
bool isRotate = false; //茶壶是否旋转
 
int wHeight = 0;
int wWidth = 0;
 
int min(int x, int y)
{
	return x < y ? x : y;
}
 
//绘制腿部
void Draw_Leg() 
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}
 
void Draw_Scene(float place[])
{
	//画茶壶
	glPushMatrix();
	glTranslatef(place[0], place[1], place[2]);//控制平移
	glRotatef(90, 1, 0, 0);
	glRotatef(tRotate, 0, 1, 0);//控制旋转
	glutSolidTeapot(1);
	glPopMatrix();
 
	//画桌面
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();
 
	//画四条腿
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
 
	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
 
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
 
	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
 
}
 
void updateView(int width, int height)
{
	glViewport(0,0,width,height); //设置视窗大小
 
	glMatrixMode(GL_PROJECTION); //设置矩阵模式为投影
	glLoadIdentity(); //初始化矩阵为单位矩阵  
 
	float whRatio = (GLfloat)width/(GLfloat)height; //设置显示比例
 
	if (bPersp){
		gluPerspective(45, whRatio, 1, 100); //透视投影
		
	}
	else
		glOrtho(-3 ,3, -3, 3,-100,100); //正投影
	    
 
	glMatrixMode(GL_MODELVIEW); //设置矩阵模式为模型
}
 
void reshape(int width, int height)
{
	if (height==0) //如果高度为0
	{
		height=1; //让高度为1（避免出现分母为0的现象）
	}
 
	height = width = min(height, width);
	wHeight = height;
	wWidth = width;
	
	updateView(wHeight, wWidth); //更新视角
}
 
void idle() 
{
	glutPostRedisplay(); //调用当前绘制函数 
}
 
float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};
float place[] = {0, 0, 5};
 
//按键回调函数
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 'q': {exit(0); break; } //退出
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; } //切换正投影、透视投影
 
	case ' ': {bAnim = !bAnim; break;} //旋转模式的切换
	case 'o': {bWire = !bWire; break;} //渲染方式的切换
 
	//整体操作
 
	case 'a': { //向左移动
		center[0] += 0.1f;
		eye[0] += 0.1f;
		break;
			  }
	case 'd': { //向右移动
		center[0] -= 0.1f;
		eye[0] -= 0.1f;
		break;
			  }
	case 'w': { //向上移动
		center[1] -= 0.1f;
		eye[1] -= 0.1f;
		break;
			  }
	case 's': { //向下移动
		center[1] += 0.1f;
		eye[1] += 0.1f;
		break;
			  }
	case 'z': { //向前移动
		center[2] -= 0.1f;
		eye[2] -= 0.1f;
		break;
			  }
	case 'c': { //向后移动
		center[2] += 0.1f;
		eye[2] += 0.1f;
		break;
			  }
 
	//茶壶相关操作
 
	case 'l': { //右移茶壶
		place[0] += 0.1f;
		if (place[0] > 1.5f)place[0] = 1.5f; //不超出桌面范围
		break;
			  }
	case 'j': { //左移茶壶
		place[0] -= 0.1f;
		if (place[0] < -1.5f)place[0] = -1.5f;
		break;
			  }
	case 'i': { //后移茶壶
		place[1] += 0.1f;
		if (place[1] > 1.5f)place[1] = 1.5f;
		break;
			  }
	case 'k': { //前移茶壶
		place[1] -= 0.1f;
		if (place[1] < -1.5f)place[1] = -1.5f;
		break;
			  }
	case 'e': { //旋转茶壶
		isRotate = !isRotate;
		break;
			  }
	}
}
 
 
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓存和深度缓存
	glLoadIdentity(); //初始化矩阵为单位矩阵
 
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);			
 
	//  观察位置(eye[0],eye[1],eye[2]
	//  物体位置(center[0],center[1],center[2]
	//  观察方向(x, y, z) 
 
	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //设置多边形绘制模式：正反面，线型  
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //设置多边形绘制模式：正反面，填充  
	}
 
	glEnable(GL_DEPTH_TEST);  //开启深度测试
	glEnable(GL_LIGHTING); //开启光照模式
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 }; // 定义颜色
	GLfloat light_pos[] = {5,5,5,1};  //定义光源位置
 
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); //设置第0号光源的光照位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, white); //设置第0号光源多次反射后的光照颜色（环境光颜色）
	glEnable(GL_LIGHT0); //开启第0号光源
 
	glRotatef(fRotate, 0, 1.0f, 0);	//旋转
	glRotatef(-90, 1, 0, 0); //旋转
	glScalef(0.2, 0.2, 0.2); //缩放
	Draw_Scene(place); //场景绘制
	
	if (bAnim) fRotate += 0.5f; //茶壶桌子
	if (isRotate) tRotate += 0.5f; //茶壶旋转
 
	glutSwapBuffers(); //交换缓冲区  
}
 
int main (int argc,  char *argv[])
{
	glutInit(&argc, argv); //对glut的初始化 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//初始化显示模式:RGB颜色模型，深度测试，双缓冲   
	glutInitWindowSize(480,480); //设置窗口大小  
	int windowHandle = glutCreateWindow("Ex 3");//设置窗口标题   
 
	glutDisplayFunc(redraw); //注册绘制回调函数  
	glutReshapeFunc(reshape); //注册重绘回调函数 
	glutKeyboardFunc(key); //注册按键回调函数
	glutIdleFunc(idle); //注册全局回调函数：空闲时调用  
 
	glutMainLoop(); //glut事件处理循环
	return 0;
}
 
 
