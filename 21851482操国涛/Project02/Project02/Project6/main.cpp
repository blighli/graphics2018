
#include <stdlib.h>
#include <gl/glut.h>
#include "BallDefinition.h"
#define WIDTH 700
#define HEIGHT 700
// 每次更新 看做过去了 1 天
#define TimePast 1
#include <math.h>
// 对太阳系星球的参数进行调整用的宏
#define KK .000001
#define sk (.07 * KK)
#define k (.5 * KK)
#define vk (1.5 * KK)
#define fk (.5 * KK)
#define hfk (.4 * KK)
#define ffk (.3 * KK)
#define dk (1.07 * KK)
#define edk (1.12 * KK)
#define lsk (.3 * KK)
#define mk (15000 * KK)
#define mrk (1.6 * KK)
#define tk .3
#define ttk .2
#define tttk .1
//自转速度（都定义为定值）
#define SelfRotate 3
#define ARRAY_SIZE 10
enum 
STARS {
	Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune
};
Ball * Balls[ARRAY_SIZE];
void init() {
	Float3 Color;
	// 定义星球，这些星球的数据是经过不同比例变化过的
	// 太阳
	Float3(Color, 1, 0, 0);
	Balls[Sun] = new
		LightBall(sk * 696300000, 0, 0, SelfRotate, 0, Color);
	// 水星
	Float3(Color, .2, .2, .5);
	Balls[Mercury] = new MatBall(vk * 4880000, dk * 58000000, 87, SelfRotate, Balls[Sun], Color);
	// 金星
	Float3(Color, 1, .7, 0);
	Balls[Venus] = new MatBall(vk * 12103600, dk * 108000000, 225, SelfRotate, Balls[Sun], Color);
	// 地球
	Float3(Color, 0, 1, 0);
	Balls[Earth] = new MatBall(vk * 12756300, edk * 150000000, 365, SelfRotate, Balls[Sun], Color);
	// 月亮
	Float3(Color, 1, 1, 0);
	Balls[Moon] = new MatBall(mrk * 3844010.0f, mk * 1734.0f, 30, SelfRotate, Balls[Earth], Color);
	// 火星
	Float3(Color, 1, .5, .5);
	Balls[Mars] = new
		MatBall(
			vk * 6794000, KK * 228000000, 687, SelfRotate, Balls[Sun], Color);
	// 木星
	Float3(Color, 1, 1, .5);
	Balls[Jupiter] = new MatBall(lsk * 142984000, fk * 778000000, tk * 4328, SelfRotate, Balls[Sun], Color);
	// 土星
	Float3(Color, .5, 1, .5);
	Balls[Saturn] = new
		MatBall(
			lsk * 120536000, fk * 1427000000, ttk * 10752, SelfRotate, Balls[Sun], Color);
	// 天王星
	Float3(Color, .4, .4, .4);
	Balls[Uranus] = new MatBall(k * 51118000,hfk * 2870000000, tttk * 30664, SelfRotate, Balls[Sun], Color);
	// 海王星
	Float3(Color, .5, .5, 1);
	Balls[Neptune] = new MatBall(k * 49532000,fk * 4497000000, tttk * 60148, SelfRotate, Balls[Sun], Color);
}
// 初始视角（ 视点在(+z, -y)处 ）
#define REST (700000000 * KK)
#define REST_Z (REST)
#define REST_Y (-REST)
// lookAt参数
GLdouble eyeX = 0, eyeY = REST_Y, eyeZ = REST_Z;
GLdouble centerX = 0, centerY = 0, centerZ = 0;
GLdouble upX = 0, upY = 0, upZ = 1;
void OnDraw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.7, .7, .7, .1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	// 实际绘制
	for(int i = 0; i < ARRAY_SIZE; i++)
		Balls[i]->Draw();
	glutSwapBuffers();
}
void OnUpdate(void) {
	// 实际更新
	for(int i = 0; i < ARRAY_SIZE; i++)
		Balls[i]->Update(TimePast);
	OnDraw();
}

// 每次按键移动的距离
#define OFFSET (20000000 * KK)
// 按键操作变化视角
// w(+y方向)   a(-x方向)   d(+x方向)   x(-y方向)   s(+z 方向)   S(-z 方向)   r(reset)
void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case'w': eyeY += OFFSET; break;
	case's': eyeZ += OFFSET; break;
	case'S': eyeZ -= OFFSET; break;
	case'a': eyeX -= OFFSET; break;
	case'd': eyeX += OFFSET; break;
	case'x': eyeY -= OFFSET; break;
	case'r':eyeX = 0; eyeY = REST_Y; eyeZ = REST_Z;
			centerX = 0; centerY = 0; centerZ = 0;
			upX = 0; upY = 0; upZ = 1;break;
	case27: exit(0); break;
	default: break;
	}
}
int main(int argc, char*  argv[]) {
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(150, 50);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("PROJECT2");
	glutDisplayFunc(&OnDraw);
	glutIdleFunc(&OnUpdate);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return	0;
}