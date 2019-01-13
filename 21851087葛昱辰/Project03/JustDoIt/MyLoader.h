#ifndef __3DS_LOADER_H__
#define __3DS_LOADER_H__

#include <fstream>
#include "MyModel.h"

class MyLoader
{
public:
	MyLoader();
	void               OpenFile( const std::string& );
	void               LoadFile();
	void               CloseFile();
	const Model&       GetModel();
private:
	void               LoadModel( const Chunk& );

	void               LoadMaterial( const Chunk& );
	void               LoadColor( float* );
	void               LoadPercent( float* );

	void               LoadObject( const Chunk& );
	void               LoadVertex( Object* const& );
	void               LoadFaces( Object* );
	void               LoadObjectMaterial( Object* );
	void               LoadMesh( const Chunk& MyChunk );
private:
	Vertex             Vectors( const Vertex&, const Vertex& );
	Vertex             Cross( const Vertex&, const Vertex& );
	void               Normalize( Vertex* Point );
	void               ComputeNormals();
private:
	void               ReadChunk( Chunk* MyChunk );
	void               ReadGLfloat( GLfloat* );
	void               ReadGLushort( GLushort* );
	void               ReadGLuint( GLuint* );
	void               ReadGLubyte( GLubyte* );
	void               SkipNByte( const size_t& );
	std::string        ReadString();
private:
	size_t             NowPos;
	size_t             FileLength;
	size_t             Version;
	Model              MyModel;
	std::ifstream      FileReader;
};

#endif