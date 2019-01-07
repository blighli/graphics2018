#include "ObjLoader.h"
#include <fstream>
#include <iostream>
using namespace std;

//GLfloat m = 1.0f;

ObjLoader::ObjLoader(string filename)
{
	string line;
	fstream f;

	f.open(filename, ios::in);

	if (!f.is_open()){
		cout << "Something Went Wrong When Opening Objfiles" << endl;
	}

	while (!f.eof()){

		getline(f, line);

		vector<string>parameters;

		string tailMark = " ";

		string ans = "";

		line = line.append(tailMark);

		for (int i = 0; i < line.length(); i++) {

			char ch = line[i];
			if (ch != ' ') {
				ans+=ch;
			}
			else {
				parameters.push_back(ans);
				ans = "";
			}
		}

		//cout << parameters.size() << endl;

		if (parameters.size() != 4) {
			cout << "the size is not correct" << endl;
		}

		else {

			if (parameters[0] == "v") {

				vector<GLfloat>Point;

				for (int i = 1; i < 4; i++) {

					GLfloat xyz = atof(parameters[i].c_str());

					Point.push_back(xyz);
				}

				vSets.push_back(Point);
			}

			else if (parameters[0] == "f") {

				vector<GLint>vIndexSets;

				for (int i = 1; i < 4; i++){
					string x = parameters[i];
					string ans = "";
					for (int j = 0; j < x.length(); j++) {
						char ch = x[j];
						if (ch != '/') {
							ans += ch;
						}
						else {
							break;
						}
					}
					GLint index = atof(ans.c_str());
					index = index--;
					vIndexSets.push_back(index);
				}

				fSets.push_back(vIndexSets);
			}

			/*else if (parameters[0] == "vn") {
				vector<GLfloat>vnValueSets;
				for (int i = 1; i < 4; i++) {
					GLfloat vnxyz = atof(parameters[i].c_str());
					vnValueSets.push_back(vnxyz);
				}
				vnSets.push_back(vnValueSets);
			}

			else if (parameters[0] == "vt") {
				vector<GLfloat>vtValueSets;
				for (int i = 1; i < 4; i++) {
					GLfloat vnxyz = atof(parameters[i].c_str());
					vtValueSets.push_back(vnxyz);
				}
				vtSets.push_back(vtValueSets);
			}*/

		}
	}
	f.close();
}

//void ObjLoader::Init()
//{
//	lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
//	animationLastingTime = 0;
//}
//
//GLfloat morphRadis(vector<vector<GLfloat>>x) {
//	GLfloat maxL = 0.0f;
//	for (int i = 0; i < x.size(); i++) 
//	{
//		GLfloat vertex[3];
//		vertex[0] = (x[i])[0];
//		vertex[1] = (x[i])[1];
//		vertex[2] = (x[i])[2];
//
//		GLfloat L = sqrt(vertex[0] * vertex[0] + vertex[1] * vertex[1] + vertex[2] * vertex[2]);
//		if (L > maxL) {
//			maxL = L;
//		}
//	}
//
//	return maxL;
//}



void ObjLoader::Draw(){

	//GLfloat morphR = morphRadis(vSets);
	//cout << morphR << endl;

	//const GLint animationEndTime = 4000;

	//GLint currentFrameTime = glutGet(GLUT_ELAPSED_TIME);

	//animationLastingTime += currentFrameTime - lastFrameTime;

	/*GLfloat step = (GLfloat)animationLastingTime / animationEndTime;
	
	if (step > 1.0f) {
		step = 1.0f;
		glutSolidSphere(morphR, 40, 50);
	}*/

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < fSets.size(); i++) {

		GLfloat VN[3];

		//three vertex represrnt a surface
		GLfloat SV1[3];
		GLfloat	SV2[3];
		GLfloat SV3[3];

		/*GLfloat EV1[3];
		GLfloat	EV2[3];
		GLfloat EV3[3];

		GLfloat SV1[3];
		GLfloat	SV2[3];
		GLfloat SV3[3];*/

		if ((fSets[i]).size() != 3) {
			cout << "the fSetsets_Size is not correct" << endl;
		}

		else {

				GLint firstVertexIndex = (fSets[i])[0];
				GLint secondVertexIndex = (fSets[i])[1];
				GLint thirdVertexIndex = (fSets[i])[2];

				/*V1[0] = (vSets[firstVertexIndex])[0];
				V1[1] = (vSets[firstVertexIndex])[1];
				V1[2] = (vSets[firstVertexIndex])[2];

				V2[0] = (vSets[secondVertexIndex])[0];
				V2[1] = (vSets[secondVertexIndex])[1];
				V2[2] = (vSets[secondVertexIndex])[2];

				V3[0] = (vSets[thirdVertexIndex])[0];
				V3[1] = (vSets[thirdVertexIndex])[1];
				V3[2] = (vSets[thirdVertexIndex])[2];*/
				SV1[0] = (vSets[firstVertexIndex])[0];
				SV1[1] = (vSets[firstVertexIndex])[1];
				SV1[2] = (vSets[firstVertexIndex])[2];

				SV2[0] = (vSets[secondVertexIndex])[0];
				SV2[1] = (vSets[secondVertexIndex])[1];
				SV2[2] = (vSets[secondVertexIndex])[2];

				SV3[0] = (vSets[thirdVertexIndex])[0];
				SV3[1] = (vSets[thirdVertexIndex])[1];
				SV3[2] = (vSets[thirdVertexIndex])[2];

				/*GLfloat lv1 = sqrt(V1[0] * V1[0] + V1[1] * V1[1] + V1[2] * V1[2]);
				GLfloat lv2 = sqrt(V2[0] * V2[0] + V2[1] * V2[1] + V2[2] * V2[2]);
				GLfloat lv3 = sqrt(V3[0] * V3[0] + V3[1] * V3[1] + V3[2] * V3[2]);

				GLfloat proportion1 = lv1 / morphR;
				GLfloat proportion2 = lv2 / morphR;
				GLfloat proportion3 = lv3 / morphR;

				EV1[0] = V1[0] / proportion1;
				EV1[1] = V1[1] / proportion1;
				EV1[2] = V1[2] / proportion1;

				EV2[0] = V2[0] / proportion2;
				EV2[1] = V2[1] / proportion2;
				EV2[2] = V2[2] / proportion2;

				EV3[0] = V3[0] / proportion3;
				EV3[1] = V3[1] / proportion3;
				EV3[2] = V3[2] / proportion3;

				SV1[0] = EV1[0] * step + (1 - step) * V1[0];
				SV1[1] = EV1[1] * step + (1 - step) * V1[1];
				SV1[2] = EV1[2] * step + (1 - step) * V1[2];

				SV2[0] = EV2[0] * step + (1 - step) * V2[0];
				SV2[1] = EV2[1] * step + (1 - step) * V2[1];
				SV2[2] = EV2[2] * step + (1 - step) * V2[2];

				SV3[0] = EV3[0] * step + (1 - step) * V3[0];
				SV3[1] = EV3[1] * step + (1 - step) * V3[1];
				SV3[2] = EV3[2] * step + (1 - step) * V3[2];*/

				//if there is no vn in the objfile
				//if (vnSets.size() == 0) {
					GLfloat vec1[3], vec2[3], vec3[3];
					//(x2-x1,y2-y1,z2-z1)
					vec1[0] = SV1[0] - SV2[0];
					vec1[1] = SV1[1] - SV2[1];
					vec1[2] = SV1[2] - SV2[2];

					//(x3-x2,y3-y2,z3-z2)
					vec2[0] = SV1[0] - SV3[0];
					vec2[1] = SV1[1] - SV3[1];
					vec2[2] = SV1[2] - SV3[2];

					//(x3-x1,y3-y1,z3-z1)
					vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
					vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
					vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

					GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

					VN[0] = vec3[0] / D;
					VN[1] = vec3[1] / D;
					VN[2] = vec3[2] / D;

					glNormal3f(VN[0], VN[1], VN[2]);
				//}

				//if already have vn
				/*else {
					if (i < vnSets.size()) {
						VN[0] = (vnSets[i])[0];
						VN[1] = (vnSets[i])[1];
						VN[2] = (vnSets[i])[2];
						glNormal3f(VN[0], VN[1], VN[2]);
					}
				}*/

				glVertex3f(SV1[0], SV1[1], SV1[2]);
				glVertex3f(SV2[0], SV2[1], SV2[2]);
				glVertex3f(SV3[0], SV3[1], SV3[2]);
				
		}
	}

	glEnd();

	//lastFrameTime = currentFrameTime;
}

