#ifndef BITMAP24_H
#define BITMAP24_H

#include <fstream>
#include <string>
#include <gl\glut.h>

class Bitmap24
{
public:
	explicit Bitmap24(const std::string & name)
		:_name(name)
	{
		std::locale::global(std::locale(""));
		std::ifstream fin(_name.c_str(), std::ifstream::binary);
		std::locale::global(std::locale("C"));
		if(!fin)
		{throw std::runtime_error("error: unable to open input file: " + _name);}
		fin.seekg(0x0012, std::fstream::beg);
		fin.read(reinterpret_cast<char *>(&_width), sizeof(_width));
		fin.read(reinterpret_cast<char *>(&_height), sizeof(_height));
		_data = new GLubyte[getSizeImage()];
		fin.seekg(0x36, std::fstream::beg);
		fin.read(reinterpret_cast<char *>(_data), getSizeImage());
		fin.close();
	}
	virtual ~Bitmap24(GLvoid) throw()
	{
		delete []_data;
	}
	GLsizei getWidth(GLvoid) const throw()
	{
		
		return _width;
	}
	GLsizei getHeight(GLvoid) const throw()
	{
		return _height;
	}
	GLubyte * getData(GLvoid) const throw()
	{
		return _data;
	}
	GLvoid display(GLvoid) const throw()
	{
		glDrawPixels(getWidth(), getHeight(),
			GL_BGR_EXT, GL_UNSIGNED_BYTE, getData());
	}
	GLuint getTexture() const throw()
	{
		static GLuint result(0);
		static GLint i(0);
		if(i++ == 0)
		{
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 
				0, GL_BGR_EXT, GL_UNSIGNED_BYTE, getData());
		}
		i = 1;
		return result;
	}
private:
	explicit Bitmap24(const Bitmap24 &);
	Bitmap24 & operator = (const Bitmap24 &);
	GLuint getSizeImage(GLvoid) const throw()
	{
		return (((getWidth() * getBitCount() + 0x1f) & 0xffffffe0) / 0x8) * getHeight();
	}
	GLushort getBitCount(GLvoid) const throw()
	{
		return 24;
	}
	std::string _name;
	GLsizei  _width;
	GLsizei  _height;
	GLubyte * _data;
};

#endif
