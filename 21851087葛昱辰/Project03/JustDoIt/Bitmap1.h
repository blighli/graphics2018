#ifndef BITMAP1_H
#define BITMAP1_H

#include <fstream>
#include <string>
#include <gl\glut.h>

class Bitmap1
{
public:
	explicit Bitmap1(const std::string & name)
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
		fin.seekg(0x3e, std::fstream::beg);
		fin.read(reinterpret_cast<char *>(_data), getSizeImage());
		fin.close();
	}
	virtual ~Bitmap1(GLvoid) throw()
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
		glBitmap(getWidth(), getHeight(), 0, 0, 0, 0, getData());
	}
	void save(const std::string & name) const
	{
		std::locale::global(std::locale(""));
		std::ofstream fout(name.c_str(), std::ofstream::binary);
		std::locale::global(std::locale("C"));
		if(!fout)
		{throw std::runtime_error("error: unable to open or build input 0file:" + name);}
		fout.write(reinterpret_cast<char *>(getData()), getSizeImage());
		fout.close();
	}
private:
	explicit Bitmap1(const Bitmap1 &);
	Bitmap1 & operator = (const Bitmap1 &);
	GLuint getSizeImage(GLvoid) const throw()
	{
		return (((getWidth() * getBitCount() + 0x1f) & 0xffffffe0) / 0x8) * getHeight();
	}
	GLushort getBitCount(GLvoid) const throw()
	{
		return 1;
	}
	std::string _name;
	GLsizei _width;
	GLsizei _height;
	GLubyte * _data;
};

#endif