#version 400 core

out vec4 color;

uniform vec3 light_position;
uniform vec3 light_position2;

in DATA{
	vec3 surfaceNormal;
	vec3 WorldPosition;
	vec4 color1;
}fs_in;

void main(){

	vec3 norm;
	vec3 toLight;
	vec3 toLight2;
	float diffuse;
	float diffuse2;

	norm = normalize(fs_in.surfaceNormal);
	toLight = normalize(light_position - fs_in.WorldPosition);
	toLight2 = normalize(light_position2 - fs_in.WorldPosition);

	diffuse = max(dot(norm, toLight), 0.0);
	diffuse2 = max(dot(norm, toLight2), 0.0);

	color = vec4(diffuse*vec3(0.7,0.7,0.78),1.0) + vec4(diffuse2*vec3(0.7,0.7,0.78),1.0);
}