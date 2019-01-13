#version 400

in vec3 fragPos;
in vec3 pass_normal;

out vec4 out_color;

uniform vec3 lightPos;
uniform vec3 viewPos;

vec3 objColor = vec3(1.0f,0.5f,0.0f);
vec3 lightColor = vec3(0.6f,0.6f,0.6f);

struct Material{
  float diffuse;
  float specular;
  float shineiness;
};


struct DirLight {
    vec3 direction;
	  vec3 lightColor;
};

struct SpotLight{

  vec3 position;
  vec3 direction;
  float cutoff;
  float outcutoff;

  float constant;
  float linear;
  float quadratic;

  vec3 lightColor;
};

uniform Material material;
uniform SpotLight spotlight1,spotlight2;
uniform DirLight dirlight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewPos);


void main(){

  vec3 norm = normalize(pass_normal);
  vec3 viewDir = normalize(viewPos - fragPos);

  vec3 result = calculateSpotLight(spotlight1,norm,fragPos,viewDir);
  result += calculateSpotLight(spotlight2,norm,fragPos,viewDir);

  out_color = vec4(result,1.0f);

}


vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
  vec3 lightDir = normalize(light.position - fragPos);

  float theta = dot(lightDir,normalize(-light.direction));

  if(theta > light.outcutoff){

    vec3 ambient = light.lightColor * 0.1;

    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = light.lightColor * diff * material.diffuse;

    //当viewDir和reflectDir夹角大于90度的时候就会出问题，会减去光照值
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shineiness);
    // vec3 specular = light.lightColor * spec * material.specular;

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outcutoff;
    float intensity = clamp((theta - light.outcutoff) / epsilon,0.0, 1.0);

    diffuse *= intensity;
    //diffuse *= attenuation;
    //specular *= attenuation;

    return ambient + diffuse;
  }
  else{
    return light.lightColor * 0.01;
  }
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
  vec3 lightDir = normalize(-light.direction);

  float diff = max(dot(lightDir,normal),0.0f);

  vec3 reflectDir =reflect(-lightDir, normal);
  float spec = pow(max(dot(reflectDir,viewDir),0.0f),material.shineiness);

  return light.lightColor * (diff * material.diffuse + spec * material.specular + 0.1);
}
