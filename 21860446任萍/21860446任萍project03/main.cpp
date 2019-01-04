#include<windows.h>
#include <stdlib.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
GLfloat *currentCoeff;
GLenum currentPlane;
GLint currentGenMode;
float roangles = 45.0;
#define stripeImageWidth 32
GLubyte stripeImage[4 * stripeImageWidth];
//自定义初始化opengl函数

void makeStripeImage(void) { //生成纹理
	for (int j = 0; j < stripeImageWidth; j++) {
		stripeImage[4 * j + 0] = (GLubyte)((j <= 4) ? 255 : 0);
		stripeImage[4 * j + 1] = (GLubyte)((j > 4) ? 255 : 0);
		stripeImage[4 * j + 2] = (GLubyte)0;
		stripeImage[4 * j + 3] = (GLubyte)255;
	}
}
void init(void)
{
	GLfloat xequalzero[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat slanted[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	makeStripeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//纹理映射
	glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//纹理环境
	currentCoeff = xequalzero;
	currentGenMode = GL_OBJECT_LINEAR;
	currentPlane = GL_OBJECT_PLANE;
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);//自动生成纹理坐标,设定生成纹理的平面参考方式
	glTexGenfv(GL_S, currentPlane, currentCoeff);//来设定这个平面
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_1D);
	//glShadeModel(GL_SMOOTH);
	// 设置光源
	GLfloat sun_light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat sun_light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);//第0号光源位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);//0号光源环境光属性
	//经过很多次反射后最终遗留在环境中的光线强度（颜色）
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);//散射光属性
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//镜面反射光属性

	//OPENGL在后面的渲染中使用光照，默认情况下是关闭的
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CW);
	// 设置材质
	GLfloat earth_mat_ambient[] = { 0.5f, 1.0f, 0.5f, 1.0f };
	GLfloat earth_mat_diffuse[] = { 0.5f, 1.0f, 0.5f, 1.0f };
	GLfloat earth_mat_specular[] = { 0.0f, 0.5f, 0.5f, 1.0f };
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat earth_mat_shininess = 50.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);//材质环境颜色
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);//材质散射颜色
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);//材质镜面反射颜色
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);//材质发射光颜色
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);//镜面反射指数
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(roangles, 0.0, 0.0, 1.0);
	//glTranslatef(Move_x, Move_y, Move_z);
	glutSolidSphere(1.0, 32, 32);
	glPopMatrix();

	//glEnable/glDisable —— 开启和关闭服务器端GL功能
	glDisable(GL_DEPTH_TEST);//启用深度测试
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_1D);//对活动的材质进行贴图
	glDisable(GL_LIGHTING);//关闭光源
	glDisable(GL_LIGHT0);//关闭光源，
	glDisable(GL_AUTO_NORMAL);//执行后，图形能把光反射到各个方向
	glDisable(GL_NORMALIZE);//在转换之后和光照之前将法线向量标准化成单位长度
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	//设置投影参数
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//正交投影
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-1.5*(GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

	//设置模型参数--几何体参数
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("球");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}
