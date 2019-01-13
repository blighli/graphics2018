#include <iostream>
#include <windows.h>
#include <time.h>

#include "Source/model/models.h"
#include "Source/graphics/Window.h"
#include "Source/graphics/shader.h"
#include "Source/graphics/buffer/indexbuffer.h"
#include "Source/graphics/buffer/vertexarray.h"
#include "Source/maths/maths_func.h"
#include "Source/graphics/cameraRPG.h"
#include "Source/model/texture.h"
#include "Source/model/panel.h"
#include "Source/graphics/modelMove.h"
#include "soil.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define Window_TITLE "ZJU GAME DEVELOPEMENT"

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

Window window = Window(Window_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

using namespace std;

vec3 lightPos = vec3(0, 5, 5);


int main() {

	printf("W,A,S,D控制方向\n");
	printf("Q,E旋转\n");
	printf("鼠标滚轮缩放\n");
	printf("鼠标按下滚轮拖动旋转\n");

	printf("I,J,K,L控制模型移动方向\n");
	printf("U,O旋转模型\n");

	mat4 view = mat4();

	CameraRPG camera = CameraRPG(vec3(0.0f, 0.0f, 0.0f), vec3(-20.0f, 20.0f, 20.0f));
	ModelMove modelMove;
	Panel p;

	Model dragon = Model("Source/model/dragon.obj");
	dragon.init();

	Shader dragonShader = Shader("Source/shaders/basic.vert", "Source/shaders/basic.frag");
	dragonShader.enable();
	dragonShader.setUniform3f("lightPos", lightPos);
	dragonShader.setUniformMat4("proj_matrix", mat4::perspective(45, 1.67, 0.1, 300));
	dragonShader.setUniformMat4("model_matrix", mat4::translation(vec3(0, 0, 0)));
	
	dragonShader.setUniform3f("spotlight1.position", vec3(15, 15, 0));
	dragonShader.setUniform3f("spotlight1.direction", vec3(-1, -1, 0));
	dragonShader.setUniform1f("spotlight1.cutoff", cos(mat4::toRadians(20.5)));
	dragonShader.setUniform1f("spotlight1.outcutoff", cos(mat4::toRadians(25.5)));
	dragonShader.setUniform1f("spotlight1.constant", 1.0f);
	dragonShader.setUniform1f("spotlight1.linear", 0.09f);
	dragonShader.setUniform1f("spotlight1.quadratic", 0.032f);
	dragonShader.setUniform3f("spotlight1.lightColor",vec3(0.0,0.0,0.8));

	dragonShader.setUniform3f("spotlight2.position", vec3(-15, 15, 0));
	dragonShader.setUniform3f("spotlight2.direction", vec3(1, -1, 0));
	dragonShader.setUniform1f("spotlight2.cutoff", cos(mat4::toRadians(20.5)));
	dragonShader.setUniform1f("spotlight2.outcutoff", cos(mat4::toRadians(25.5)));
	dragonShader.setUniform1f("spotlight2.constant", 1.0f);
	dragonShader.setUniform1f("spotlight2.linear", 0.09f);
	dragonShader.setUniform1f("spotlight2.quadratic", 0.032f);
	dragonShader.setUniform3f("spotlight2.lightColor", vec3(0.8, 0.0, 0.0));

	dragonShader.setUniform3f("dirlight.direction", vec3(0.0f, -1.0f, 0.0f));
	dragonShader.setUniform3f("dirlight.lightColor", vec3(1, 1, 1));
	
	dragonShader.setUniform1f("material.shininess", 32.0f);
	dragonShader.setUniform1f("material.diffuse", 1.0f);
	dragonShader.setUniform1f("material.specular", 0.5f);
	dragonShader.disable();

	

	GLfloat preXPos = WINDOW_WIDTH / 2, preYPos = WINDOW_HEIGHT / 2;
	bool isFirstPress = true;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;


	while (!window.closed()) {

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		modelMove.move(&window, deltaTime);
		camera.update(&window, preXPos, preYPos, deltaTime, isFirstPress);
		mat4 view = camera.getViewMatrix();
		mat4 model = modelMove.getModelMatrix();
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		window.clear();

		dragonShader.enable();
		dragonShader.setUniformMat4("view_matrix", view);
		dragonShader.setUniformMat4("model_matrix", model);
		dragonShader.setUniform3f("viewPos", camera.getCameraPos());
		dragon.render();
		p.render();
		dragonShader.disable();

		

		window.update();

	}

	return 0;
}


