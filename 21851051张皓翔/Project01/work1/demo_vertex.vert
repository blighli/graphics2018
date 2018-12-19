<<<<<<< HEAD
#version 450 core
uniform mat4 MVP;
attribute vec3 vCol;
attribute vec2 vPos;
varying vec3 color;

void main(){
	gl_Position = MVP * vec4(vPos, 0.0, 1.0);
	color = vCol;
=======
#version 450 core
uniform mat4 MVP;
attribute vec3 vCol;
attribute vec2 vPos;
varying vec3 color;

void main(){
	gl_Position = MVP * vec4(vPos, 0.0, 1.0);
	color = vCol;
>>>>>>> a8afaeee6689758db9e975ec51ec225f49416c7b
}