#version 440 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;

in vec2 texPos;
in vec3 NewLightPos;

uniform sampler2D ourTexture;
uniform vec4 NowlightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;

float specularStrength = 0.5f;

void main(){


	vec3 lightColor = vec3(NowlightColor);

	float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

	vec4 texColor = texture(ourTexture,texPos);

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * lightColor;


	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (diffuse  + specular + ambient ) * vec3(texColor);

	color = vec4(result,1.0f);


}