#include"texturebuffer.h"
#include<iostream>
Texture::Texture(const char* paths, GLuint componentCount, GLuint textUnit): m_ComponentCount(componentCount)
{
	m_TextUnit = textUnit;
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data1;
	data1 = stbi_load(paths, &width, &height, &nrChannels, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);  //图片载入到纹理对象上
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);
}
Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID);
}
void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + m_TextUnit);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);                                 //封装绑定
}
void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);                                          //封装解绑
}
void Texture::aBind() const
{
	glActiveTexture(GL_TEXTURE0 + m_TextUnit);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}