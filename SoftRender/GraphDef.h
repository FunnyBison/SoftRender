#ifndef GRAPHDEF_H
#define GRAPHDEF_H

#include "Vector3D.h"
struct Color
{
	float r;
	float g;
	float b;
};

struct TexturePos
{
	float u;
	float v;
};

struct Vertex
{
	Vector3d pos;		//位置
	Color c;			//颜色
	TexturePos t;		//纹理坐标
	Vector3d norm;		//法向量
	Vector3d world;		//世界坐标
};

struct Triangle
{
	int vIndex[3];		//自身坐标存储的顶点坐标
	Vector3d norm;		//面法向量
	int texId;			//纹理编号
};

#endif
