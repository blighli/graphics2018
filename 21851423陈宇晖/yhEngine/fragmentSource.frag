#version 330 core									
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

/* 材质 */
struct Material {
    vec3 ambient;		//物体环境光
    sampler2D diffuse;	//漫反射贴图
    sampler2D specular;	//镜面贴图
    float shininess;	//镜面高光倍率
};

/* 平行光 */
struct LightDirectional{
	vec3 pos;		//光所在的位置
	vec3 color;		//光的颜色
	vec3 dirToLight;//平行光·方向
};

/* 点光源 */
struct LightPoint {
	vec3 pos;		//光所在的位置
	vec3 color;		//光的颜色
	vec3 dirToLight;//光方向

	float constant;	//常数项
	float linear;	//一次项
	float quadratic;//二次项
};

/* 聚光灯 */
struct LightSpot{
	vec3 pos;		//光所在的位置
	vec3 color;		//光的颜色
	vec3 dirToLight;//光方向

	float constant;	//常数项
	float linear;	//一次项
	float quadratic;//二次项

	float cosPhyInner;
	float cosPhyOutter;
};

uniform Material material;
uniform LightDirectional lightD;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;

uniform vec3 objColor;
uniform vec3 ambientColor;

uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

out vec4 FragColor;

/* 根据平行光和相机位置计算光的方向 */
vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera){

	// diffuse = max( dot(uL, uN), 0) 
	/* 光线和法线的夹角越大 漫反射越小 反之越大 */
	float diffuseIntensity = max( dot( light.dirToLight, uNormal), 0);
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular = max( dot(uR, uCam）, 0)
	/* 反射光线和点到相机的夹角越大 镜面光越小 反之越大 */
	vec3 uR = normalize( reflect(-light.dirToLight, uNormal));
	float specularIntensity = pow( max( dot( uR, dirToCamera), 0), material.shininess);
	vec3 specularColor = specularIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffuseColor + specularColor;
	return result;
}

/* 根据点光源计算光的方向 */
vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera){

	// attenuation
	/* 随距离衰减 */
	float dist = length(light.pos -  FragPos);
	float attenuation =  1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	// diffuse
	/* 光源的方向不再是固定的 而是通过两点计算得出 */
	vec3 dirToLight = normalize(light.pos - FragPos);
	float diffuseIntensity = max( dot( dirToLight, uNormal), 0);
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular
	vec3 uR = normalize( reflect(-dirToLight, uNormal));
	float specularIntensity = pow( max( dot( uR, dirToCamera), 0), material.shininess);
	vec3 specularColor = specularIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = attenuation * (diffuseColor + specularColor);
	return result;
}


vec3 CalcLightSpot(LightSpot light, vec3 uNormal, vec3 dirToCamera){

	/* 计算边缘柔化 */
	float spotRatio;
	vec3 dirToLight = normalize(light.pos - FragPos);
	float cosTheta = dot( -dirToLight, -light.dirToLight);
	if(cosTheta > light.cosPhyInner){
		//inside
		spotRatio = 1.0;
	}
	else if (cosTheta > light.cosPhyOutter){
		//middle
		spotRatio=(cosTheta - light.cosPhyOutter) / (light.cosPhyInner - light.cosPhyOutter);
	}
	else{
		//outside
		spotRatio=0;
	}
	
	// attenuation
	/* 随距离衰减 */
	float dist = length(light.pos -  FragPos);
	float attenuation =  1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	// diffuse
	float diffuseIntensity = max( dot( dirToLight, uNormal), 0);
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular
	vec3 uR = normalize( reflect(-dirToLight, uNormal));
	float specularIntensity = pow( max( dot( uR, dirToCamera), 0), material.shininess);
	vec3 specularColor = specularIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = attenuation * (diffuseColor + specularColor) * spotRatio;
	return result;
}

void main(){

	vec3 finalResult = vec3(0, 0, 0);
	vec3 uNormal = normalize(Normal);
	vec3 dirToCamera = normalize(cameraPos - FragPos);
	finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP0, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3, uNormal, dirToCamera);
	finalResult += CalcLightSpot(lightS, uNormal, dirToCamera);

	FragColor = vec4(finalResult, 1.0);
//	else{
//		//outside
//		spotRatio=0;
//		FragColor = vec4((ambient + (diffuse + specular)*spotRatio ) * objColor, 1.0f);
//	}
}