#version 450 core

out vec4 fColor;
smooth in vec2 textCoordination;
uniform sampler2D texSampler;


void main(){
	fColor = texture2D(texSampler,textCoordination);
}