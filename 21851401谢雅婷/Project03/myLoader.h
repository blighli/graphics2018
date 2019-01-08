#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <vector>
#include <string>
using namespace std;

class ObjLoader{

public:

	ObjLoader(string filename);
	void Draw();

private:

	vector<vector<GLfloat>>vSets;
	vector<vector<GLint>>fSets;

};

