#version 330 core
out vec4 FragColor;
in vec2 outTexcoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   FragColor = texture(texture1, outTexcoord);
}
