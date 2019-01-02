#version 450 core

out vec4 fColor;

in vec3 fragNormal;
in vec3 fragPos;

smooth in vec2 textCoordination;

uniform sampler2D texSampler;

float ambientStrength = 0.2;

void main(){
	vec3 lightPos = vec3(0,0,0);
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 normal = normalize(fragNormal);
	float diffFactor = max(dot(lightDir,normal),0);
	vec3 ambient = ambientStrength * vec3(1,1,1);
	vec3 backColor = vec3(texture2D(texSampler,textCoordination));
	vec3 diffuseRes = diffFactor * backColor * vec3(1,1,1);
	vec3 ambientRes = ambient * backColor;
	fColor = vec4(diffuseRes,1.0) + vec4(ambientRes,1.0);
}