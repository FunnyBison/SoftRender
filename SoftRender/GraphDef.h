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
	Vector3d pos;		//λ��
	Color c;			//��ɫ
	TexturePos t;		//��������
	Vector3d norm;		//������
	Vector3d world;		//��������
};

struct Triangle
{
	int vIndex[3];		//��������洢�Ķ�������
	Vector3d norm;		//�淨����
	int texId;			//������
};

#endif
