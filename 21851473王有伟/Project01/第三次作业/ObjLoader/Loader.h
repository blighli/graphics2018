#ifndef LOADER_H_
#define LOADER_H_

#include<iostream>
#include<GL/glut.h>
#include<string>
#include<vector>


using namespace std;


typedef Vector3d Point;

class Loader {
public:
	void Load(char* filename);
	void Draw();

	vector<Point> V;
	vector<vector<int> > F;
};

#endif 
