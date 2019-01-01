#include "BallDefinition.h"
Ball::Ball(Float Radius, Float Distance, Float Speed, Float SelfSpeed, Ball * Parent) {
	Float4(Color, 0.8f, 0.8f, 0.8f, 1.0f);
	this->Radius = Radius;
	this->SelfSpeed = SelfSpeed;
	if(Speed > 0)
		this->Speed = 360.0f / Speed;
		AlphaSelf = Alpha = 0;
		this->Distance = Distance;
		ParentBall = Parent;
}
#include <stdio.h>
#include <math.h>
#define PI 3.1415926535
// 对普通的球体进行移动和旋转
void Ball::DrawBall() {
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	int n = 1440;
	glPushMatrix();
	{
		// 公转
		if(ParentBall != 0 && ParentBall->Distance > 0) {
			glRotatef(ParentBall->Alpha, 0, 0, 1);
			glTranslatef(ParentBall->Distance, 0.0, 0.0);
			glBegin(GL_LINES);
			for (int i = 0; i < n; ++i)
				glVertex2f(Distance * cos(2 * PI * i / n),
				Distance * sin(2 * PI * i / n));
				glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			for (int i = 0; i < n; ++i)
				glVertex2f(Distance * cos(2 * PI * i / n),
				Distance * sin(2 * PI * i / n));
				glEnd();
			}
		glRotatef(Alpha, 0, 0, 1);
		glTranslatef(Distance, 0.0, 0.0);
		// 自转
		glRotatef(AlphaSelf, 0, 0, 1);
		// 绘图
		glColor3f(RFloat3(Color));
		glutSolidSphere(Radius, 40, 32);
	}
	glPopMatrix();
}



void
Ball::Update(long
	TimeSpan) {

	// TimeSpan 是天

	Alpha += TimeSpan * Speed;

	AlphaSelf += SelfSpeed;

}



MatBall::MatBall(Float Radius, Float Distance, Float Speed, Float SelfSpeed,

	Ball * Parent, Float3 color) : Ball(Radius, Distance, Speed, SelfSpeed, Parent) {

	Float4(Color, color[0], color[1], color[2], 1.0f);

}



// 对材质进行设置

void
MatBall::DrawMat() {

	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };

	GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };

	GLfloat mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };

	//下面两句替换可以出现彩色或者蓝色的太阳系模型

	//GLfloat mat_emission[] = {RFloat4(Color)};

	GLfloat mat_emission[] = { .0f, .0f, .1f, 1.0f };

	GLfloat mat_shininess = 90.0f;



	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

}



LightBall::LightBall(Float Radius, Float Distance, Float Speed, Float SelfSpeed,

	Ball * Parent, Float3 color)

	: MatBall(Radius, Distance, Speed, SelfSpeed, Parent, color) {}



// 对光源进行设置

void
LightBall::DrawLight() {

	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

}


