#ifndef __DRAW_MODEL_H__
#define __DRAW_MODEL_H__

#include "MyModel.h"

class DrawModel
{
public:
	DrawModel(){}
	void SetModel( const Model& MyModel );
	GLint GetObjectNum();
private:
	std::vector< Material > MyMaterial;
	std::vector< Object > MyObject;
};

inline void DrawModel::SetModel( const Model& MyModel )
{
	MyMaterial = MyModel.MyMaterial;
	MyObject = MyModel.MyObject;
}

inline GLint GetObjectNum()
{
	
}

#endif