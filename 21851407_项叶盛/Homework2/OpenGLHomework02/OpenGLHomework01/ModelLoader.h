#pragma once
#include "Shapes.h"
class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	bool loadShapeFromFile(Shape* shape, const char* filename);
};

