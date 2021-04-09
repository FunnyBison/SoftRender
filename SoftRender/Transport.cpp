#include "Transport.h"
#include <utility>
#include <cmath>
#include "GraphDef.h"

Transport::Transport()
	:m(4, 4)
{
}


Transport::~Transport()
{
}

Transport::Transport(Transport && t)
	:m(std::move(t.m))
{
}

Transport & Transport::operator=(Transport && t)
{
	m = std::move(t.m);
	return *this;
}

/*void Transport::TransformByMatrix(const Matrix &matrix)
{
	Matrix res = Matrix::Product(m, matrix);
	m = std::move(res);
}*/

void Transport::TransformByOther(const Transport & tr)
{
	Matrix res = Matrix::Product(m, tr.m);
	m = std::move(res);
}

Transport &Transport::Translate(float x, float y, float z)
{
	Transport translation;
	translation.m.Unit();
	translation.m.Set(3, 0, x);
	translation.m.Set(3, 1, y);
	translation.m.Set(3, 2, z);

	TransformByOther(translation);
	return *this;
}

Transport & Transport::Translate(const Vector3d & tv)
{
	return Translate(tv.x, tv.y, tv.z);
}

Transport & Transport::RotateX(float angle)
{
	float cosA = cos(angle);
	float sinA = sin(angle);

	Transport rx;
	rx.m.Unit();
	rx.m.Set(1, 1, cosA);
	rx.m.Set(1, 2, sinA);
	rx.m.Set(2, 1, -sinA);
	rx.m.Set(2, 2, cosA);

	TransformByOther(rx);
	return *this;
}

Transport & Transport::RotateY(float angle)
{
	float cosA = cos(angle);
	float sinA = sin(angle);

	Transport ry;
	ry.m.Unit();
	ry.m.Set(0, 0, cosA);
	ry.m.Set(2, 0, sinA);
	ry.m.Set(0, 2, -sinA);
	ry.m.Set(2, 2, cosA);

	TransformByOther(ry);
	return *this;
}

Transport & Transport::RotateZ(float angle)
{
	float cosA = cos(angle);
	float sinA = sin(angle);

	Transport rz;
	rz.m.Unit();
	rz.m.Set(0, 0, cosA);
	rz.m.Set(0, 1, sinA);
	rz.m.Set(1, 0, -sinA);
	rz.m.Set(1, 1, cosA);

	TransformByOther(rz);
	return *this;
}

void Transport::TransformVector(Vector3d & v)
{
	Vector3d res;
	res.x = v.x * m.Get(0, 0) + v.y * m.Get(1, 0) + v.z * m.Get(2, 0) + v.w * m.Get(3, 0);
	res.y = v.x * m.Get(0, 1) + v.y * m.Get(1, 1) + v.z * m.Get(2, 1) + v.w * m.Get(3, 1);
	res.z = v.x * m.Get(0, 2) + v.y * m.Get(1, 2) + v.z * m.Get(2, 2) + v.w * m.Get(3, 2);
	res.w = v.x * m.Get(0, 3) + v.y * m.Get(1, 3) + v.z * m.Get(2, 3) + v.w * m.Get(3, 3);

	v = res;
}
