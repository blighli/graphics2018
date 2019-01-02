#include "SphereGenerator.h"

#define PI 3.1415926
//顶点数据结构：|x,y,z|s,t|x',y',z'|
SphereGenerator::SphereGenerator() {

}

SphereGenerator::SphereGenerator(float radius,int stepnum)
{
	if (stepnum < 4) {
		printf("error: in SphereGenerator() 步长过小！\n");
		exit(0);
	}
	glm::vec3 normal;
	this->radius = radius;

	stepNum = stepnum;
	stepY = PI / (stepNum + 1);
	stepRzx = PI / (stepNum);

	stepS = 1.0 / (2 * stepNum);
	stepT = 1.0 / (stepNum + 1);

	float theta = 0;
	float gama = stepY;


	vertexArray = NULL;
	vertexNum = 0;
	for (int i = 0; i < 2 * stepNum; ++i) {	//计算球体上端的三角网格
		theta = i * stepRzx;
		
		vertexVector.push_back(radius * sin(gama) * sin(theta));	
		vertexVector.push_back(radius * cos(gama));					
		vertexVector.push_back(radius * sin(gama) * cos(theta));	
		vertexVector.push_back(i*stepS);
		vertexVector.push_back(stepT);
		normal = glm::normalize(glm::vec3(radius * sin(gama) * sin(theta), radius * cos(gama), radius * sin(gama) * cos(theta)));
		vertexVector.push_back(normal.x);
		vertexVector.push_back(normal.y);
		vertexVector.push_back(normal.z);
		vertexNum++;

		vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));	
		vertexVector.push_back(radius * cos(gama));						
		vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));	
		vertexVector.push_back(i*stepS + stepS);
		vertexVector.push_back(stepT);
		normal = glm::normalize(glm::vec3(radius * sin(gama) * sin(theta + stepRzx), radius * cos(gama), radius * sin(gama) * cos(theta + stepRzx)));
		vertexVector.push_back(normal.x);
		vertexVector.push_back(normal.y);
		vertexVector.push_back(normal.z);
		vertexNum++;

		vertexVector.push_back(0.0);				//x
		vertexVector.push_back(radius);				//y
		vertexVector.push_back(0.0);				//z
		vertexVector.push_back(i*stepS);//s
		vertexVector.push_back(0);					//t
		normal = glm::normalize(glm::vec3(0.0, radius, 0.0));
		vertexVector.push_back(normal.x);
		vertexVector.push_back(normal.y);
		vertexVector.push_back(normal.z);
		vertexNum++;
	}

	for (int i = 1; i < stepNum; ++i) {	//计算球体中间的三角面环带		
		gama = i * stepY;
		for (int j = 0; j < 2 * stepNum; ++j) {	//计算其中一圈三角环带
			theta = j * stepRzx;
			//左下方三角面片
			//	1
			vertexVector.push_back(radius * sin(gama) * sin(theta));	
			vertexVector.push_back(radius * cos(gama));					
			vertexVector.push_back(radius * sin(gama) * cos(theta));	
			vertexVector.push_back(j * stepS);
			vertexVector.push_back(i * stepT);
			normal = glm::normalize(glm::vec3(radius * sin(gama) * sin(theta), radius * cos(gama), radius * sin(gama) * cos(theta)));
			vertexVector.push_back(normal.x);
			vertexVector.push_back(normal.y);
			vertexVector.push_back(normal.z);
			vertexNum++;
			//	2
			vertexVector.push_back(radius * sin(gama + stepY) * sin(theta));	
			vertexVector.push_back(radius * cos(gama + stepY));					
			vertexVector.push_back(radius * sin(gama + stepY) * cos(theta));	
			vertexVector.push_back(j * stepS);
			vertexVector.push_back(i*stepT + stepT);
			normal = glm::normalize(glm::vec3(radius * sin(gama + stepY) * sin(theta), radius * cos(gama + stepY), radius * sin(gama + stepY) * cos(theta)));
			vertexVector.push_back(normal.x);
			vertexVector.push_back(normal.y);
			vertexVector.push_back(normal.z);
			vertexNum++;
			//	3
			vertexVector.push_back(radius * sin(gama + stepY) * sin(theta + stepRzx));
			vertexVector.push_back(radius * cos(gama + stepY));
			vertexVector.push_back(radius * sin(gama + stepY) * cos(theta + stepRzx));
			vertexVector.push_back(j*stepS + stepS);
			vertexVector.push_back(i*stepT + stepT);
			normal = glm::normalize(glm::vec3(radius * sin(gama + stepY) * sin(theta + stepRzx), radius * cos(gama + stepY), radius * sin(gama + stepY) * cos(theta + stepRzx)));
			vertexVector.push_back(normal.x);
			vertexVector.push_back(normal.y);
			vertexVector.push_back(normal.z);
			vertexNum++;
			//右上方三角面片
			//	3
			vertexVector.push_back(radius * sin(gama + stepY) * sin(theta + stepRzx));
			vertexVector.push_back(radius * cos(gama + stepY));
			vertexVector.push_back(radius * sin(gama + stepY) * cos(theta + stepRzx));
			vertexVector.push_back(j*stepS + stepS);
			vertexVector.push_back(i*stepT + stepT);
			normal = glm::normalize(glm::vec3(radius * sin(gama + stepY) * sin(theta + stepRzx), radius * cos(gama + stepY), radius * sin(gama + stepY) * cos(theta + stepRzx)));
			vertexVector.push_back(normal.x);
			vertexVector.push_back(normal.y);
			vertexVector.push_back(normal.z);
			vertexNum++;

			//	4
			vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));
			vertexVector.push_back(radius * cos(gama));
			vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));
			vertexVector.push_back(j * stepS + stepS);
			vertexVector.push_back(i * stepT);			//原本这个地方忘记乘i，搞了几个小时贴图紊乱。。。。
			normal = glm::normalize(glm::vec3(radius * sin(gama) * sin(theta + stepRzx), radius * cos(gama), radius * sin(gama) * cos(theta + stepRzx)));
			vertexVector.push_back(normal.x);
			vertexVector.push_back(normal.y);
			vertexVector.push_back(normal.z);
			vertexNum++;
		
			//	1
			vertexVector.push_back(radius * sin(gama) * sin(theta));
			vertexVector.push_back(radius * cos(gama));
			vertexVector.push_back(radius * sin(gama) * cos(theta));
			vertexVector.push_back(j * stepS);
			vertexVector.push_back(i * stepT);
			normal = glm::normalize(glm::vec3(radius * sin(gama) * sin(theta), radius * cos(gama), radius * sin(gama) * cos(theta)));
			vertexVector.push_back(normal.x);
			vertexVector.push_back(normal.y);
			vertexVector.push_back(normal.z);
			vertexNum++;
		}
	}		

	gama = PI - stepY;

	for (int i = 0; i < 2 * stepNum; ++i) {	//计算球体最下端的三角网格
		theta = i * stepRzx;

		
		//球体最下方的点
		vertexVector.push_back(0);
		vertexVector.push_back(-radius);
		vertexVector.push_back(0);
		vertexVector.push_back(i*stepS + stepS);
		vertexVector.push_back(1);
		normal = glm::normalize(glm::vec3(0, -radius, 0));
		vertexVector.push_back(normal.x);
		vertexVector.push_back(normal.y);
		vertexVector.push_back(normal.z);
		vertexNum++;
		//第三个点
		vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));
		vertexVector.push_back(radius * cos(gama));
		vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));
		vertexVector.push_back(i*stepS + stepS);
	    vertexVector.push_back(1 - stepT);
		normal = glm::normalize(glm::vec3(radius * sin(gama) * sin(theta + stepRzx), radius * cos(gama), radius * sin(gama) * cos(theta + stepRzx)));
		vertexVector.push_back(normal.x);
		vertexVector.push_back(normal.y);
		vertexVector.push_back(normal.z);
		vertexNum++;

		//第一个点
		vertexVector.push_back(radius * sin(gama) * sin(theta));
		vertexVector.push_back(radius * cos(gama));
		vertexVector.push_back(radius * sin(gama) * cos(theta));
		vertexVector.push_back(i*stepS);
		vertexVector.push_back(1 - stepT);
		normal = glm::normalize(glm::vec3(radius * sin(gama) * sin(theta), radius * cos(gama), radius * sin(gama) * cos(theta)));
		vertexVector.push_back(normal.x);
		vertexVector.push_back(normal.y);
		vertexVector.push_back(normal.z);
		vertexNum++;
	}

	SynthesisArray();
}


SphereGenerator::~SphereGenerator()
{
}

void SphereGenerator::PrintVertexInfo() {
	if (vertexArray == NULL) {
		printf("error: in PrintVertexInfo() 不存在顶点数组信息！\n");
		return;
	}
	int index = 1;
	for (int i = 0; i < vertexNum*8; i += 8) {
		printf("顶点 %d —— 坐标XYZ : (%.4f , %.4f, %.4f)  纹理ST：(%.4f , %.4f)  法向量：（%.4f, %.4f, %.4f）\n", index, vertexArray[i], vertexArray[i + 1], vertexArray[i + 2],
			vertexArray[i + 3], vertexArray[i + 4], vertexArray[i + 5], vertexArray[i + 6],
			vertexArray[i + 7]);
		index += 1;
	}
}

void SphereGenerator::SynthesisArray() {
	if (vertexVector.empty()) {
		printf("error: in SynthesisArray() 不存在顶点向量记录！\n");
		return;
	}
	vertexArray = (GLfloat*)malloc(sizeof(GLfloat) * vertexVector.size());
	if (vertexArray) {
		memcpy(vertexArray, &vertexVector[0], sizeof(GLfloat) * vertexVector.size());
	}
	else {
		printf("error: in SynthesisArray() 申请空间失败!\n");
	}
}