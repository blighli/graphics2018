#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox1;

uniform float factor;
void main()
{    
    FragColor =  texture(skybox1, TexCoords);
}