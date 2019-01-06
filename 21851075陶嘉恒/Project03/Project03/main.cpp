/* 
** skyboxes.h/.cpp  创建天空盒、树木、地形等。包含：读取树木、地形纹理，随机生成树木
** dynamic.h/.cpp	创建火焰动态纹理。
** model.h/.cpp		读取OBJ模型
*/

//需要包含的头文件
#include"skyboxes.h"
#include "model.h"
#include "dynamic.h"
#include <stdio.h>
#include <glut/glut.h>



#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 500
#define BUFSIZE	     1000

//摄像机离物体的距离
float G_fDistance = 1.5f;
//物体的旋转角度 
float G_fAngle_horizon = 0.0;
float G_fAngle_vertical = 0.0f;

//摄像机的X Y
GLfloat observe_x = -6.0f;
GLfloat observe_y = 0.0;
GLfloat observe_angle = 90.0f;
GLfloat observe_angle1 = 0.0f;
GLfloat observe_r = 3.0f;
GLfloat observe_z = -0.7f;
const GLfloat PI = 3.24159265357f;
const GLfloat angToarc = 3.141592 / 180.0;	//角度化弧度
const GLfloat arcToang = 180.0 / 3.141592;	//弧度化角度



GLfloat xx = 0.0f;
GLfloat yy = 0.0f;
GLfloat zz = 0.0f;

//设定读入的模型以及显示的方式
bool redraw = true;
Objmodel *obj1 = new Objmodel();
string path1 = "obj/rubby.obj";
vector<GLfloat > center1(3);
Objmodel *obj2 = new Objmodel();
string path2 = "obj/bird.obj";
vector<GLfloat > center2(3);
Objmodel *obj3 = new Objmodel();
string path3 = "obj/torus.obj";
vector<GLfloat > center3(3);
GLint mode1 = GL_FILL;
GLint mode2 = GL_TRIANGLES;

//light0参数
GLfloat Vp0[] = { 0.0,200.0,0.0,0 };	//光源环境光位置
GLfloat Va0[] = { 0.8,0.8,0.8,1 };       //光源环境光强度数组  
GLfloat Vd0[] = { 0.6,0.6,0.6,1 };       //光源散射光强度数组  
GLfloat Vs0[] = { 0.5,0.5,0.5,1 };       //光源镜面反射光强度数组  


//鼠标控制视点
int prex = 0;
int prey = 0;
//视点移动的距离 == 天空盒将要移动的距离
GLfloat movedis_x = 0.0f;
GLfloat movedis_z = 0.0f;
GLfloat view_dis_skybox_x = 0.0f;
GLfloat view_dis_skybox_z = 0.0f;
GLfloat terrain_height = 0.0f;
const int TREE_NUM = 100;
GLfloat treex[TREE_NUM];
GLfloat treez[TREE_NUM];
GLint   treetexturenum[TREE_NUM];
GLfloat tree_angle = 0.0f;
Skybox *skybox;
DynamicTexture *fire = new DynamicTexture();

int mode_s = GL_RENDER;
int window_w = 0;
int window_h = 0;

vector<vector<float > >obj_pos;
int obj_nums = 0;


///函数
void myinit(void);
void myReshape(GLsizei w, GLsizei h);
void display(void);
void moveMouse(int x, int y);
void processSpecialKeys(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void pickObjection(int button, int state, int x, int y);
void drawObjection(int mode);
void motion(int x, int y);

int compare(const void *value1, const void *value2)
{
	return *(int*)value1 - *(int*)value2;
}

void drawGround(GLfloat begin, GLfloat end, GLfloat interval, GLfloat y) {

	for (GLfloat i = begin; i <= end; i += interval) {
		glBegin(GL_LINES);
		glVertex3f(begin, y, i);
		glVertex3f(end, y, i);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(i, y, begin);
		glVertex3f(i, y, end);
		glEnd();
	}

}

int k = 0;
static int last = clock();
void f() {

	//设置成模型矩阵模式
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int now = clock();
	if (now - last > 100) {
		k = (k + 1) % 8;
		last = now;
		//cout << last << endl;
		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);


	cout << "程序操作方式说明：" << endl;
	cout << "w/s/a/d操作视点前后左右移动" << endl;
	cout<<"鼠标上下左右控制视点方向" << endl;
	cout<<"左击OBJ模型不放，左右移动鼠标可以移动OBJ模型 " << endl;
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	//设定OPENGL窗口位置和大小
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("编程作业3：复杂三维模型显示");


	myinit();
		glutReshapeFunc(myReshape);
		glutSpecialFunc(processSpecialKeys);
		glutPassiveMotionFunc(moveMouse);	//鼠标移动旋转视角
		glutMouseFunc(pickObjection);		//鼠标点击选择
		glutMotionFunc(motion);				//鼠标按下移动OBJ
		glutKeyboardFunc(processNormalKeys);
		glutDisplayFunc(display);
		glutIdleFunc(f);					//闲时也能画火苗
		glutMainLoop();
	return 0;
}


void myinit(void)
{
	//your initialization code
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float low = -MAP_SCANL * MAP_W / 2 + 5;
	float length = MAP_SCANL * MAP_W - 5;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < TREE_NUM; i++) {
		treex[i] = rand() % (int)length + low;
		treez[i] = rand() % (int)length + low;
		treetexturenum[i] = rand() % 4;		//这里的4代表树木的纹理个数   
		//因为是树木的纹理个数在类实例化后才知道	所以无法再init里面就给出  这里只好手动给定具体值
	}
	
	fire->loadTexImages();
}

void myReshape(GLsizei w, GLsizei h)
{
	//设定视区
	glViewport(0, 0, w, h);

	//设定透视方式
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, 1.0*(GLfloat)w / (GLfloat)h, 0.1, 3000.0);
	window_w = w;
	window_h = h;
}

void display(void)
{
	//cout << "123123" << endl;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//设置成模型矩阵模式
	glMatrixMode(GL_MODELVIEW);
	skybox = new Skybox();
	//载入单位化矩阵
	glLoadIdentity();
	
	gluLookAt(observe_x, observe_y + terrain_height, observe_z,
		observe_r*cos(observe_angle*angToarc) + observe_x, observe_y + 4 * sin(observe_angle1*angToarc) + terrain_height, observe_z + observe_r*sin(observe_angle*angToarc),
		0.0, 1.0, 0.0);
	tree_angle += observe_angle/100;


	//画天空盒 
	skybox->loadTexImages();
	glPushMatrix();
	terrain_height = skybox->getHeight(observe_x, observe_z) + 5.0f;
	skybox->moveSkyBox(view_dis_skybox_x, terrain_height, view_dis_skybox_z);
	//绘制物体

	if (redraw) {		//只读一遍   不然每次调用会很卡
		obj1->readFile(path1);
		obj2->readFile(path2);
		obj3->readFile(path3);
		center1 = obj1->getCenter();
		center2 = obj2->getCenter();
		center3 = obj3->getCenter();

		center1[0] = 50.0f - center1[0]; center1[2] = 50.0f - center1[2]; center1[1] *= -1;
		obj_pos.push_back(center1);
		center2[0] = -center2[0] - 50; center2[2] = -center2[2] + 50; center2[1] *= -1;
		obj_pos.push_back(center2);
		center3[0] = -center3[0]; center3[2] = -center3[2] + 200; center3[1] *= -1;
		obj_pos.push_back(center3);
		redraw = false;
	}
	drawObjection(mode_s);
	//计算视点向量
	float n1[2];
	float x1 = observe_r*cos(observe_angle*angToarc); float z1 = observe_r*sin(observe_angle*angToarc);
	//归一化
	n1[0] = x1 / sqrtf(x1 * x1 + z1 * z1);
	n1[1] = z1 / sqrtf(x1 * x1 + z1 * z1);
	//n1为俯视图上视点单位向量，n1⊥n2则  n2[2] = {-z,x};  可以使n1·n2 = 0
	float n2[2] = { -n1[1],n1[0] };
	if (time(NULL) - last > 150) {
		k = (k + 1) % 8;
		last = clock();
	}

	skybox->drawTrees(treex, treez, TREE_NUM, n2, treetexturenum);
	glTranslatef(-10.0, 0.0, 10.0);
	fire->drawFire(k, n2);
	glPopMatrix();

	
	glLightfv(GL_LIGHT0, GL_POSITION, Vp0);		//设置光源的位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, Va0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Vd0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Vs0);

	glTranslatef(0.0, 0.0, -G_fDistance);
	
	
	//绘制地平线
	/*GLfloat begin = -100.0f;
	GLfloat end = 100.0f;
	GLfloat interval = 1.0f;
	GLfloat obeserve_y = -1.0f;
	drawGround(begin, end, interval, obeserve_y);*/
									
	glutSwapBuffers();//交换前后缓冲区
		//glFlush();
}

void moveMouse(int x, int y) {
	observe_angle = (x / 4) % 720;
	observe_angle1 = ((WINDOW_HEIGHT / 2 - y) / 10) % 90 + 10;
	prex = x;
	prey = y;
	if (x <= 0)
		x = WINDOW_WIDTH;
	glutPostRedisplay();
}


void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
		
	case GLUT_KEY_LEFT:
		observe_angle -= 2.0f; break;
	case GLUT_KEY_RIGHT:
		observe_angle += 2.0f; break;
	case GLUT_KEY_UP:
		if (observe_angle1 <= 90.0f)
			observe_angle1 += 1.0f;
		break;
	case GLUT_KEY_DOWN:
		if (observe_angle1 >= -90.0f)
			observe_angle1 -= 1.0f;
		break;
	}
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'y':	//"a"
		G_fDistance -= 2.0f;
		break;
	case 'Y':		//"A"
		G_fDistance += 2.0f;
		break;
	case 27:	//"esc"
		exit(0);
	case '1':
		path1 = "obj/rubby.obj";
		redraw = true; obj1->~Objmodel(); obj1 = new Objmodel(); break;
	case '2':
		path1 = "obj/bird.obj";
		redraw = true; obj1->~Objmodel(); obj1 = new Objmodel(); break;
	case '3':
		path1 = "obj/torus.obj";
		redraw = true; obj1->~Objmodel(); obj1 = new Objmodel(); break;
	case '4':
		path1 = "obj/wan.obj";
		redraw = true; obj1->~Objmodel(); obj1 = new Objmodel(); break;
	case '5':
		mode2 = GL_POINTS; break;
	case '6':
		mode2 = GL_TRIANGLES; mode1 = GL_LINE; break;
	case '7':
		mode1 = GL_FILL; mode2 = GL_TRIANGLES; break;
	case 'W':
	case 'w':
		movedis_x = 1.0* cos(observe_angle*angToarc) * cos(observe_angle1*angToarc);
		movedis_z = 1.0* sin(observe_angle*angToarc) * cos(observe_angle1*angToarc);
		view_dis_skybox_x += movedis_x;
		view_dis_skybox_z += movedis_z;
		observe_x += /*0.1f*/ movedis_x;
		observe_z += /*0.1f*/ movedis_z;
		break;
	case 'S':
	case 's':
		movedis_x = -1.0* cos(observe_angle*angToarc) * cos(observe_angle1*angToarc);
		movedis_z = -1.0* sin(observe_angle*angToarc) * cos(observe_angle1*angToarc);
		view_dis_skybox_x += movedis_x;
		view_dis_skybox_z += movedis_z;
		observe_x += /*0.1f*/ movedis_x;
		observe_z += /*0.1f*/ movedis_z;
		break;
	case 'A':
	case 'a':
		movedis_x = -1.0* cos((observe_angle + 90.0)*angToarc);
		movedis_z = -1.0* sin((observe_angle + 90.0)*angToarc);
		view_dis_skybox_x += movedis_x;
		view_dis_skybox_z += movedis_z;
		observe_x += /*0.1f*/ movedis_x;
		observe_z += /*0.1f*/ movedis_z;
	
		break;
	case 'D':
	case 'd':
		movedis_x = 1.0* cos((observe_angle + 90.0)*angToarc);
		movedis_z = 1.0* sin((observe_angle + 90.0)*angToarc);
		view_dis_skybox_x += movedis_x;
		view_dis_skybox_z += movedis_z;
		observe_x += /*0.1f*/ movedis_x;
		observe_z += /*0.1f*/ movedis_z;
	
		break;
	}
	//printf("视点坐标：X:%f,Y:%f,Z:%f\n", observe_x, observe_y + terrain_height, observe_z);
	glutPostRedisplay();
}

//鼠标按下移动事件
void motion(int x, int y) {
	moveMouse(x, y);	//视角变化
	int num = obj_nums - 1;
	if (num < 0 || num >= obj_pos.size())
		return;
	float dis = sqrtf((observe_x - obj_pos[num][0])*(observe_x - obj_pos[num][0]) + (observe_z - obj_pos[num][2])*(observe_z - obj_pos[num][2]));
	obj_pos[num][0] = dis*cos(observe_angle*angToarc) + observe_x;
	obj_pos[num][2] = observe_z + dis*sin(observe_angle*angToarc);
	glutPostRedisplay();
}



void drawObjection(int mode) {

	if (mode == GL_SELECT) {
		glInitNames();
	}
	glPushMatrix();
	float obj_high1 = skybox->getHeight(obj_pos[0][0], obj_pos[0][2]) + 6.0f;
	glTranslatef(obj_pos[0][0], obj_pos[0][1] + obj_high1, obj_pos[0][2]);
	glScalef(3.0f, 3.0f, 3.0f);
	if (mode == GL_SELECT)
		glPushName(1);
	obj1->drawBox();
	obj1->showObj(mode1, mode2);	//参数为模型的显示方式  GL_POINTS	GL_LINES	GL_TRIANGLES
	if (mode == GL_SELECT)
		glPopName();
	glPopMatrix();

	glPushMatrix();
	float obj_high2 = skybox->getHeight(obj_pos[1][0], obj_pos[1][2]) + 1.5f;
	glTranslatef(obj_pos[1][0] , obj_pos[1][1] + obj_high2, obj_pos[1][2]);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(3.0f, 3.0f, 3.0f);
	if (mode == GL_SELECT)
		glPushName(2);
	obj2->drawBox();
	obj2->showObj(mode1, mode2);	//参数为模型的显示方式  GL_POINTS	GL_LINES	GL_TRIANGLES
	if (mode == GL_SELECT)
		glPopName();
	glPopMatrix();

	glPushMatrix();
	float obj_high3 = skybox->getHeight(obj_pos[2][0], obj_pos[2][2]) + 3.0f;
	glTranslatef(obj_pos[2][0], obj_pos[2][1] + obj_high3, obj_pos[2][2]);
	glScalef(0.01, 0.01, 0.01);
	if (mode == GL_SELECT)
		glPushName(3);
	obj3->drawBox();
	obj3->showObj(mode1, mode2);	//参数为模型的显示方式  GL_POINTS	GL_LINES	GL_TRIANGLES
	if (mode == GL_SELECT)
		glPopName();
	glPopMatrix();
}

void processHits(GLint hits, GLuint buffer[])
{
	GLuint  names, *ptr;
	vector<int> n;
	ptr = (GLuint *)buffer;
	for (int i = 0; i < hits; i++) {
		names = *ptr;
		if (names == 0) {
			ptr += 3;
			continue;
		}
		if (names != 1) {
			obj_nums = 0;
			continue;
		}
		ptr += 3;
		for (int j = 0; j < names; j++) {
			obj_nums = *ptr;
		}
	}
	//cout << obj_nums<< endl;
}



void pickObjection(int button, int state, int x, int y)
{
	GLuint selectBuf[BUFSIZE];   //存储点击记录
	GLint hits;                                 //点击记录的个数
	GLint viewport[4];                    //视口

	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;

	glGetIntegerv(GL_VIEWPORT, viewport);  //获得视口

	glSelectBuffer(BUFSIZE, selectBuf);    //指定存储点击记录的数组
	glRenderMode(GL_SELECT);          //进入选择模式
	

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	//设置挑选矩阵，挑选区域的中心坐标是(x,viewport[3]-y)，大小是(5,5)
	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 5, 5, viewport);
	//设置投影矩阵
	
	gluPerspective(80.0f, float(window_w) / float(window_h), 0.1, 3000.0);
	//gluOrtho2D(0.0, 3.0, 0.0, 3.0);
	//在选择模式下绘制方块

	mode_s = GL_SELECT;
	display();
	mode_s = GL_RENDER;
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();        //绘制结束

	hits = glRenderMode(GL_RENDER); //获取记录下的点击的个数
	processHits(hits, selectBuf);           //处理点击记录selectBuf
	
	glutPostRedisplay();
}