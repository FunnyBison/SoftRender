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
