
#include <iostream>


#include "Render Engine/basics/window.h"
#include "Render Engine/toolbox/maths/maths_func.h"
#include "Render Engine/shaders/dragonshader.h"
#include "Render Engine/buffers/buffer.h"
#include "Render Engine/buffers/indexbuffer.h"
#include "Render Engine/buffers/vertexarray.h"
#include "Source/entity/models.h"
#include "Source/main/camera.h"
#include "World/time/Calendar.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720





int main() {

	Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Model dragon("Resource/dragon.obj");
	
	DragonShader shader("Source/shaders/dragon.vert", "Source/shaders/dragon.frag");

	shader.enable();
	
	shader.projection_matrix->load(mat4::perspective(45, (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 300));
	shader.light_position->load( vec3(0.0,10.0,-5.0));
	shader.light_position2->load( vec3(0.0,10.0,5.0));

	


	Camera camera(&window);

	//Calendar cal(0, 7 / 24);
	
	
	

	while (!window.closed()) {
		window.clear();

		dragon.render();

		camera.move();

		shader.view_matrix->load(camera.CreateViewMatrix());

		window.update();
		//cal.update(0.05, &window);
	}

	return 0;
}