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



int main() {

	printf("W,A,S,D控制方向\n");
	printf("Q,E旋转\n");
	printf("鼠标滚轮缩放\n");
	printf("鼠标按下滚轮拖动旋转\n");



	Model sun_model = Model("Source/model/sun.obj");
	Model earth_model = Model("Source/model/earth.obj");
	Model moon_model = Model("Source/model/moon.obj");

	//加载纹理贴图
	Texture sun_tex = Texture("Source/model/sun.jpg");
	Texture earth_tex = Texture("Source/model/earth.jpg");
	Texture moon_tex = Texture("Source/model/moon.jpg");
	


	float positions[8] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
	VertexArray vao;
	vao.addBuffer(new Buffer(positions, 8, 2), 0);


	Shader earthshader("Source/shaders/basic.vert", "Source/shaders/basic.frag");
	earthshader.enable();
	earthshader.setUniform3f("lightPos", vec3(0, 0 , 0));
	earthshader.setUniform4f("NowlightColor", vec4(0.9, 0.9, 0.9, 1.0));
	earthshader.setUniformMat4("perspective_matrix", mat4::perspective(45, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 200.0f));
	earthshader.disable();

	Shader sunShader("Source/shaders/basic.vert", "Source/shaders/sun.frag");
	sunShader.enable();
	sunShader.setUniformMat4("perspective_matrix", mat4::perspective(45, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 200.0f));
	sunShader.disable();

	mat4 view = mat4();

	CameraRPG camera = CameraRPG(vec3(0.0f, 0.0f, -5.0f), vec3(5.0f, 5.0f, 5.0f));

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;


	GLfloat preXPos = WINDOW_WIDTH / 2, preYPos = WINDOW_HEIGHT / 2;
	bool isFirstPress = true;



	while (!window.closed()) {


		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera.update(&window, preXPos, preYPos, deltaTime, isFirstPress);
		mat4 view = camera.getViewMatrix();


		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		window.clear();

		sun_tex.bind();
		sunShader.enable();
		sunShader.setUniformMat4("view_matrix", view);
		sunShader.setUniform3f("viewPos", camera.getCameraPos());
		sunShader.setUniformMat4("model_matrix", mat4::scale(vec3(2, 2, 2)));
		sun_model.render();
		sunShader.disable();
		sun_tex.unbind();


		earth_tex.bind();
		earthshader.enable();
		earthshader.setUniformMat4("view_matrix", view);
		earthshader.setUniform3f("viewPos", camera.getCameraPos());
		earthshader.setUniformMat4("model_matrix", mat4::translation(vec3(0, 0, -8)) * mat4::rotation(-90,vec3(0,1,0)));
		earth_model.render();
		earthshader.disable();
		earth_tex.unbind();


		moon_tex.bind();
		earthshader.enable();
		earthshader.setUniformMat4("model_matrix", mat4::translation(vec3(2, 0, -5)) * mat4::scale(vec3(0.5, 0.5, 0.5)));
		moon_model.render();
		moon_tex.unbind();
		earthshader.disable();
		earthshader.disable();



		window.update();

	}

	return 0;
}


