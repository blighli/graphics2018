#ifndef CAR_H
#define CAR_H

#include <cmath>
#include <iostream>
#include <string>
#include "MyLoader.h"

class Car
{
public:
	explicit Car(const std::string & name)
		:_name(name), Y(19.54f), HZ (51.76f), QZ (-50.8), QX (-28.0f), 
		_turning(0), _distance(0), _displacementX(0),  _displacementY(0), _speed(0), _spin(0), 
		_b(0)
	{
		MyLoader Loader;
		Loader.OpenFile( _name );
		Loader.LoadFile();
		Loader.CloseFile();
		_tempModel = Loader.GetModel();
	}
	GLvoid draw(GLvoid) const
	{
		glPushMatrix();
		glTranslatef(_displacementX, 0, _displacementY);
		glTranslatef(0, 0, -HZ);
		glRotatef(_spin, 0, 1.0, 0);
		glTranslatef(0, 0, HZ);
		drawRear();
		drawRightFront();
		drawLeftFront();
		drawBody();
		glPopMatrix();
	}
	GLvoid redisplay(GLvoid)
	{
		_displacementX += getSpeed() * sin(_spin / 57.3f);
		_displacementY += getSpeed() * cos(_spin / 57.3f);
		if((_distance += _speed) > 360.0f)
			_distance -= 360.0f;
		if(getSpeed() != 0)_spin += getTuringRadian();
		if(getSpeed() != 0)turn();
	}
	GLfloat getDisplacementX(void) const
	{
		return _displacementX;
	}
	GLfloat getDisplacementY(void) const
	{
		return _displacementY;
	}
	GLvoid turnRight(const GLfloat & f)
	{
		_turning -= f;
		if(_turning < -60.0f)
			_turning = -60.0f;
		else if(_turning > 60.0f)
			_turning = 60.0f;
	}
	GLvoid turnLeft(const GLfloat & f)
	{
		_turning += f;
		if(_turning < -60.0f)
			_turning = -60.0f;
		else if(_turning > 60.0f)
			_turning = 60.0f;
	}
	GLvoid accelerate(const GLfloat & f)
	{
		_speed += f;
	}
	GLvoid decelerate(const GLfloat & f)
	{
		_speed -= f;
	}
	GLvoid brake(GLvoid)
	{
		_b = 1;
		_speed = 0;
	}
	GLfloat getTurning(GLvoid) const
	{
		return _turning;
	}
private:
	GLfloat getDistance(GLvoid) const
	{
		return _distance;
	}
	GLfloat getSpeed(GLvoid) const
	{
		return _speed;
	}

	GLfloat getTuringRadian(GLvoid) const
	{
		return _turning / 57.3f;
	}
	GLvoid turn(GLvoid)
	{
		if(_turning > 10.0f) _turning -= 10.0f;
		else if(_turning < -10.0f) _turning += 10.0f;
		else _turning = 0.0f;
	}
	GLvoid drawBody(GLvoid) const
	{
		for(GLint i (4); i != _tempModel.MyObject.size(); ++i)
		{
			glPushMatrix();
			drawPart(_tempModel.MyObject[i]);
			glPopMatrix();
		}
	}
	GLvoid drawRightFront(GLvoid) const
	{
		glPushMatrix();
		glTranslatef(QX, -Y, -QZ);
		glRotatef(_turning, 0, 1.0, 0);
		glRotatef(_distance, 1.0f, 0.0f, 0);
		glTranslatef(-QX, Y, QZ);
		drawPart(_tempModel.MyObject[2]);
		glPopMatrix();
	}
	GLvoid drawLeftFront(GLvoid) const
	{
		glPushMatrix();
		glTranslatef(-QX, -Y, -QZ);
		glRotatef(_turning, 0, 1.0, 0);
		glRotatef(_distance, 1.0f, 0.0f, 0);
		glTranslatef(QX, Y, QZ);
		drawPart(_tempModel.MyObject[3]);
		glPopMatrix();
	}
	GLvoid drawRear(GLvoid) const
	{
		glPushMatrix();
		glTranslatef(0, -Y, -HZ);
		glRotatef(_distance, 1.0f, 0, 0);
		glTranslatef(0, Y, HZ);
		drawPart(_tempModel.MyObject[0]);
		drawPart(_tempModel.MyObject[1]);
		glPopMatrix();
	}
	GLvoid drawPart(const Object & object) const
	{
		glBegin( GL_TRIANGLES );	
		for(int j = 0; j != object.Faces.size(); j++)
		{
			const Face& ThisFace = object.Faces[ j ];
			const Material& MyMaterial = _tempModel.MyMaterial[ ThisFace.MaterialPos ];

			glNormal3f( ThisFace.Normal.x, ThisFace.Normal.y, ThisFace.Normal.z );
			
			glColor4f( MyMaterial.diffuseColor[ 0 ], MyMaterial.diffuseColor[ 1 ],
			           MyMaterial.diffuseColor[ 2 ], MyMaterial.transparency );
			for( size_t k = 0; k != 3; ++ k )
			{
				size_t index = object.Faces[ j ].Index[ k ];
				glVertex3f( object.Vertexs[ index ].x, object.Vertexs[ index ].y, object.Vertexs[ index ].z );
			}
		}
		glEnd();
	}
	std::string _name;
	Model _tempModel;
	GLfloat Y;
	GLfloat HZ;
	GLfloat QZ;
	GLfloat QX;
	GLfloat _turning;
	GLfloat _distance;
	GLfloat _speed;
	GLfloat _spin;
	GLfloat _displacementX;
	GLfloat _displacementY;
	GLboolean _b;
};

#endif