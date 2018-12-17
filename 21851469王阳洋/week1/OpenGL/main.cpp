#include <iostream>
#include <windows.h>
#include <time.h>


#include "Source/model/model.h"
#include "Source/utilities/objutils.h"
#include "Source/graphics/Window.h"
#include "Source/graphics/shader.h"
#include "Source/graphics/buffer/indexbuffer.h"
#include "Source/graphics/buffer/vertexarray.h"
#include "Source/maths/maths_func.h"
#include "Source/graphics/cameraRPG.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define Window_TITLE "ZJU GAME DEVELOPEMENT"

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

Window window = Window(Window_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

using namespace std;



int main() {

	printf("W,A,S,D控制方向\n");
	printf("Q,E旋转\n");
	printf("鼠标滚轮缩放\n");
	printf("鼠标按下滚轮拖动旋转\n");

	vector <vec3> vertexes;
	vector <vec3> normals;
	vector<vec3> colors;

	Model model = ObjUtils::readObj("Source/model/cube.obj");

	//模型加载
	for (int i = 0; i < model.m_vertexIndices.size(); i++) {
		for (int j = 0; j < 3; j++) {
			int v_index = model.m_vertexIndices[i].index[j];
			vertexes.push_back(model.m_vertexes[v_index]);
		}
	}

	int count = 0;
	for (int i = 0; i < model.m_vertexIndices.size(); i++) {
		for (int j = 0; j < 3; j++) {
			int n_index = model.m_normalIndices[i].index[j];
			normals.push_back(model.m_normals[n_index]);
			colors.push_back(vec3(0.8, 1.0, 1.0));
		}
	}


	VertexArray vao;
	vao.addBuffer(new Buffer(&vertexes[0].x, vertexes.size() * 3, 3), 0);
	vao.addBuffer(new Buffer(&normals[0].x, normals.size() * 3, 3), 1);
	vao.addBuffer(new Buffer(&colors[0].x, colors.size() * 3, 3), 2);

	Shader shader("Source/shaders/basic.vert", "Source/shaders/basic.frag");

	shader.enable();
	shader.setUniform3f("lightPos", vec3(50, 100 , 50));
	shader.setUniformMat4("perspective_matrix", mat4::perspective(45, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 200.0f));
	shader.disable();

	
	mat4 view = mat4();

	CameraRPG camera = CameraRPG(vec3(0.0f, 0.0f, 0.0f), vec3(3.0f, 3.0f, 3.0f));

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;


	GLfloat preXPos = WINDOW_WIDTH / 2, preYPos = WINDOW_HEIGHT / 2;
	bool isFirstPress = true;

	float preTime = GetTickCount();
	float startTime = GetTickCount(); 
	vec4 colorday = vec4(1.0f, 1.0f, 1.0f,1.0f);
	vec4 colornight = vec4(0.2f, 0.2f, 0.6f, 1.0f);
	int isDay = 1;

	int MAXCOUNT = 20;

	vector <mat4> buf;
	buf.resize(MAXCOUNT);
	std::vector <int> matrixFormat = { 4,4,4,4 };
	

	while (!window.closed()) {

		float nowTime = GetTickCount();
		if (nowTime - preTime > 10) {//降低帧数

			GLfloat currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			camera.update(&window, preXPos, preYPos, deltaTime, isFirstPress);
			mat4 view = camera.getViewMatrix();
		
			shader.enable();
			shader.setUniformMat4("view_matrix", view); 
			shader.setUniform4f("NowlightColor", vec4(0.6f, 0.8f, 0.9f, 1.0));
			shader.setUniform3f("viewPos", camera.getCameraPos());
			shader.disable();


			glClearColor(0.6f,0.8f,0.9f,1.0f);
			window.clear();
			
			shader.enable();
			vao.bind();
			glDrawArrays(GL_TRIANGLES, 0, vertexes.size());
			vao.unbind();
			shader.disable();


			window.update();
		}
	}

	return 0;
}


