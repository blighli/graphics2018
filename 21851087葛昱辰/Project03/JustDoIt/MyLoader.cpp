#include "MyLoader.h"
#include <stdexcept>
#include <cmath>
#include "3dsId.h"

using namespace std;

MyLoader::MyLoader() : NowPos( 0 ),FileLength( 0 ), Version( 0 )
{}
/*
*功能：读取文件
*说明：打开文件前需要加locale::global以保证可以正确打开中文名称文件，
*      另外需要以二进制方式打开，以保证所有文件能够正确读取
*/
void MyLoader::OpenFile( const string& FileRoad )
{
	locale::global( locale("") );
	FileReader.open( FileRoad.c_str(), ifstream::binary );
	locale::global( locale("C") );
	if( !FileReader )
		throw std::runtime_error( "打开文件失败" );;
}
/*
*功能：关闭文件流
*说明：暂无
*/
void MyLoader::CloseFile()
{
	FileReader.close();
}
/*
*功能：加载3DS文件
*说明：其他所有辅助函数都是为实现此功能，实现加载头3DS文件的有用信息
*/
void MyLoader::LoadFile()
{
	Chunk MyChunk;
	ReadChunk( &MyChunk );
	if( PRIMARY != MyChunk.ID )
		throw runtime_error( "文件损坏" );
	FileLength = MyChunk.Len;

	ReadChunk( &MyChunk );
	ReadGLuint( &Version );
	while( NowPos < FileLength )
	{
		ReadChunk( &MyChunk );	
		if( MAINOBJECT == MyChunk.ID )
			LoadModel( MyChunk );
		else
			SkipNByte( MyChunk.Len - 6 );
	}

	ComputeNormals();
	//MyModel.BuildList();
}
/*
*功能：加载模型
*说明：加载模型的有用数据
*/
void MyLoader::LoadModel( const Chunk& MyChunk )
{
	size_t BeginPos( NowPos - 6 );
	Chunk TempChunk;
	while( NowPos - BeginPos != MyChunk.Len )
	{
		ReadChunk( &TempChunk );
		switch( TempChunk.ID )
		{
		case OBJECT:
			LoadObject( TempChunk );
			break;

		case MATERIAL:
			LoadMaterial( TempChunk );
			break;

		default:
			SkipNByte( TempChunk.Len - 6 );
		}
	}
}
/*
*功能：加载所有对象
*功能：此处仅仅提取网个对象
*/
void MyLoader::LoadObject( const Chunk& MyChunk )
{
	Object object;
	object.Name = ReadString();
	MyModel.MyObject.push_back( object );

	Chunk ThisChunk;
	size_t BeginPos( NowPos - 7 - object.Name.size() );
	while( NowPos - BeginPos != MyChunk.Len )
	{
		ReadChunk( &ThisChunk );
		if( OBJECT_MESH == ThisChunk.ID )
			LoadMesh( ThisChunk );
		else
			SkipNByte( ThisChunk.Len - 6 );
	}
}
/*
*功能：加载网格对象
*说明：网格对象包括顶点，面，关联材质库的材质位置等
*/
void MyLoader::LoadMesh( const Chunk& MyChunk )
{
	Object &object = MyModel.MyObject[ MyModel.MyObject.size() - 1 ];

	size_t BeginPos( NowPos - 6 );
	Chunk ThisChunk;
	while( NowPos - BeginPos != MyChunk.Len )
	{
		ReadChunk( &ThisChunk );
		switch( ThisChunk.ID )
		{
		case OBJECT_VERTICES:  //顶点
			LoadVertex( &object );
			break;

		case OBJECT_FACES:     //面
			LoadFaces( &object );
			break;

		case OBJECT_MATERIAL:  //材质
			LoadObjectMaterial( &object );
			break;

		default:              //跳过不需要的块
			SkipNByte( ThisChunk.Len - 6 );
		}
	}
}
/*
*功能：加载Object的关联的材质列表
*说明：加载的不是直接的材质，加载的是材质在材质数组中的位置
*/
void MyLoader::LoadObjectMaterial( Object* object )
{
	string Name = ReadString();
	int Pos( -1 );
	for( size_t i = 0; i != MyModel.MyMaterial.size(); ++ i )
	{
		if( MyModel.MyMaterial[ i ].name == Name )
			Pos = i;
	}

	if( Pos == -1 )
		throw runtime_error( "没有找到该材质" );

	GLushort Sum( 0 ); GLushort FacePos( 0 );
	ReadGLushort( &Sum );
	for( size_t i = 0; i != Sum; ++ i )
	{
		ReadGLushort( &FacePos );
		object->Faces[ FacePos ].MaterialPos = Pos;
	}
}
/*
*功能：加载模型所需所有材质
*说明：模型所需要的所有材质都在此加载入材质库
*/
void MyLoader::LoadMaterial( const Chunk& MyChunk )
{
	
	Chunk TempChunk;
	Material material;
	size_t BeginPos( NowPos - 6 );

	while( NowPos - BeginPos < MyChunk.Len )
	{
		ReadChunk( &TempChunk );
		switch( TempChunk.ID )
		{
		case MATNAME:                       //材质名称
			material.name = ReadString();
			break;
		case MAT_AMBIENT:                  //材质Ambient
			LoadColor( material.ambientColor );
			break;
		case MAT_DIFFUSE:                  //材质Diffuse
			LoadColor( material.diffuseColor );
			break;
		case MAT_SPECULAR:                 //材质Specular
			LoadColor( material.specularColor );
			break;
		case MAT_SHININESS:                //材质Shininess
			LoadPercent( &material.shininess );
			break;
		case MAT_TRANSPARENCY:             //材质透明度
			LoadPercent( &material.transparency );
			break;
		default:
			SkipNByte( TempChunk.Len - 6 );
		}
	}
	MyModel.MyMaterial.push_back( material );
}
/*
*功能：加载材质颜色
*说明：3DS文件的材质颜色存储有两种形式，一种是（0~255）的整数形式存储，
*      占用一个字节；另一种是（0.0~1.0）的浮点型存储，占用四个字节
*/
void MyLoader::LoadColor( float* color )
{
	Chunk TempChunk;
	ReadChunk( &TempChunk );
	switch( TempChunk.ID )
	{
	case COLOR_F:
		ReadGLfloat( &color[ 0 ] );
		ReadGLfloat( &color[ 1 ] );
		ReadGLfloat( &color[ 2 ] );
		break;
	case COLOR_24:
		GLubyte Byte;
		for( size_t i = 0; i != 3; ++ i )
		{
			ReadGLubyte( &Byte );
			color[ i ] = Byte / 255.0;
		}
		break;
	default:
		SkipNByte( TempChunk.Len - 6 );
	}
}
/*
*功能：加载百分数
*说明：材质的Shininess和透明度是一个百分数，但是百分数有两种
*      一种但用两个字节，存储的是百分数的分子整数部分；另一种
*      是占用四字节，是一个浮点数
*/
void MyLoader::LoadPercent( GLfloat* Temp )
{
	Chunk TempChunk;
	ReadChunk( &TempChunk );
	switch( TempChunk.ID )
	{
	case INT_PERCENTAGE:    //Int型 百分数
		GLushort Percent;
		ReadGLushort( &Percent );
		*Temp = Percent / 100.0;
		break;
	case FLOAT_PERCENTAGE:  //Float型 百分数
		ReadGLfloat( Temp );
		break;
	default:
		SkipNByte( TempChunk.Len - 6 );
	}
}
/*
*功能：解释两顶点为一矢量
*说明：暂无
*/
Vertex MyLoader::Vectors( const Vertex& lPoint, const Vertex& rPoint )
{
	Vertex Point;
	Point.x = lPoint.x - rPoint.x;
	Point.y = lPoint.y - rPoint.y;
	Point.z = lPoint.z - rPoint.z;
	return Point;
}
/*
*功能：计算两矢量的叉积
*说明：计算平面法向量
*/
Vertex MyLoader::Cross( const Vertex& lPoint, const Vertex& rPoint )
{
	Vertex Point;
	Point.x = lPoint.y * rPoint.z - lPoint.z * rPoint.y;
	Point.y = lPoint.z * rPoint.x - lPoint.x * rPoint.z;
	Point.z = lPoint.x * rPoint.y - lPoint.y * rPoint.x;
	return Point;
}
/*
*功能：单位化矢量
*说明：计算光照所用
*/
void MyLoader::Normalize( Vertex* point )
{
	float Magnitude = sqrt( point->x * point->x + point->y * point->y + point->z * point->z );
	if( 0 == Magnitude )
		Magnitude = 1;
	point->x /= Magnitude;				
	point->y /= Magnitude;				
	point->z /= Magnitude;											
}
/*
*功能：为所有平面计算法向量
*说明：暂无
*/
void MyLoader::ComputeNormals()
{
	for( size_t i = 0; i != MyModel.MyObject.size(); ++ i )
	{
		Object& object = MyModel.MyObject[ i ];
		for( size_t j = 0; j != MyModel.MyObject[ i ].Faces.size(); ++ j )
		{
			Face& face = object.Faces[ j ];
			const Vertex &Point1 = object.Vertexs[ face.Index[ 0 ] ];
			const Vertex &Point2 = object.Vertexs[ face.Index[ 1 ] ];
			const Vertex &Point3 = object.Vertexs[ face.Index[ 2 ] ];

			face.Normal = Cross( Vectors( Point1, Point3 ), Vectors( Point3, Point2 ) );
			Normalize( &face.Normal );
		}
	}
}
/*
*功能：返回模型对象
*说明：此处以引用方式返回，容易造成外值被修改
*/
const Model& MyLoader::GetModel()
{
	return MyModel;
}
/*
*功能：加载图形所有的面（3ds max是以三角形面存储的）
*说明：面是以顶点索引的形式存储在文件中的，每三个索引是一个面，
*      但两组索引之间有一个两个字节的边界，需要跳过
*/
void MyLoader::LoadFaces( Object* ThisObject )
{
	GLushort Sum( 0 );
	ReadGLushort( &Sum );
	Face face; GLushort Temp( 0 );
	for( size_t i = 0; i != Sum; ++ i )
	{
		for( size_t j = 0; j != 4; ++ j )
		{
			ReadGLushort( &Temp );
			if( j < 3 )
				face.Index[ j ] = Temp;
		}
		ThisObject->Faces.push_back( face );
	}
}
/*
*功能：加载顶点信息
*说明：此处需要注意的3DS max的坐标系统与OpenGL不同，需要
*      将Y，Z轴交换并且交换后Z轴取反
*/
void MyLoader::LoadVertex( Object* const& ThisObject )
{
	GLushort Sum( 0 );
	ReadGLushort( &Sum );
	Vertex Point;
	float Num( 0 );float distence( 0 );
	for( size_t i = 0; i != Sum; ++ i )
	{

		ReadGLfloat( &Point.x );
		ReadGLfloat( &Point.z );
		ReadGLfloat( &Point.y );
		Point.z *= -1;
		ThisObject->Vertexs.push_back( Point );
	}
}

void MyLoader::ReadChunk( Chunk* MyChunk )
{
	ReadGLushort( &MyChunk->ID );
	ReadGLuint( &MyChunk->Len );
}

void MyLoader::ReadGLubyte( GLubyte* Ubyte )
{
	FileReader.read( reinterpret_cast< char* >( Ubyte ), sizeof( GLubyte ) );
	NowPos += sizeof( GLubyte );
}

void MyLoader::ReadGLushort( GLushort* Ushort )
{
	FileReader.read( reinterpret_cast< char* >( Ushort ), sizeof( GLushort ) );
	NowPos += sizeof( GLushort );
}

void MyLoader::ReadGLuint( GLuint* Uint )
{
	FileReader.read( reinterpret_cast< char* >( Uint ), sizeof( GLuint ) );
	NowPos += sizeof( GLuint );
}

void MyLoader::ReadGLfloat( GLfloat* Float )
{
	FileReader.read( reinterpret_cast< char* >( Float ), sizeof( GLfloat ) );
	NowPos += sizeof( GLfloat );
}

std::string MyLoader::ReadString()
{
	char alpha;	string TempWord;
	while( FileReader.get( alpha ), alpha != 0 )
		TempWord += alpha;
	NowPos += TempWord.size() + 1;
	return TempWord;
}

void MyLoader::SkipNByte( const size_t& Num )
{
	FileReader.seekg( Num, ifstream::cur );
	NowPos += Num;
}
