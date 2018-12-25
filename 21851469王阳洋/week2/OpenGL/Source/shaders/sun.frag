#version 440 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
//in vec3 NowColor;
in vec2 texPos;


uniform sampler2D ourTexture;
uniform vec4 NowlightColor;
uniform vec3 viewPos;

float specularStrength = 0.4f;

void main(){

	color = texture(ourTexture,texPos);


}