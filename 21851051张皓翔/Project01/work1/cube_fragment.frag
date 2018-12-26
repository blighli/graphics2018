#version 460 core

in vec3 vertColor;
in vec2 textCoordination;
out vec4 FColor;
uniform sampler2D tex;

void main(){
	FColor = texture2D(tex, vec2(textCoordination.s, -textCoordination.t));

}