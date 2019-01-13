#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <vector>
#include <string>
using namespace std;

class ObjLoader{

public:

	ObjLoader(string filename);
	//void Init();
	void Draw();

private:

	//GLint lastFrameTime;
	//GLint animationLastingTime;

	vector<vector<GLfloat>>vSets;
	vector<vector<GLint>>fSets;
	//vector<vector<GLfloat>>vnSets;
	//vector<vector<GLfloat>>vtSets;

};

