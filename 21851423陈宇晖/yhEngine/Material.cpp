#include "Material.h"




Material::Material(Shader * _shader, unsigned int _diffuse, unsigned int _specular, glm::vec3 _ambient, float _shininess):
	shader(_shader),
	diffuse(_diffuse),
	specular(_specular),
	ambient(_ambient),
	shininess(_shininess)
{
	
}

Material::~Material()
{
}
