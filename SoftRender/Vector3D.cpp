#include "Vector3D.h"

#include "Matrix.h"
#include <cmath>

Vector3d const Vector3d::Zero = { 0,0,0,1 };
Vector3d &Vector3d::operator =(std::initializer_list<float> initList)
{
	auto it = initList.begin();
	x = *it++;
	y = *it++;
	z = *it++;
	if (it != initList.end()) {
		w = *it++;
	}
	else {
		w = 1.0f;
	}
	return *this;
}

float Vector3d::DotProduct(const Vector3d & v1, const Vector3d & v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z * v2.z;
}

Vector3d Vector3d::CrossProduct(const Vector3d & v1, const Vector3d & v2)
{
	Vector3d ret;
	float a = v1.x;
	float b = v1.y;
	float c = v1.z;
	float d = v2.x;
	float e = v2.y;
	float f = v2.z;

	ret.x = b*f - c*e;
	ret.y = -(a*f - c*d);
	ret.z = a*e - b*d;

	return ret;
}

float Vector3d::Module()
{
	return sqrt(DotProduct(*this, *this));
}

void Vector3d::Normalize()
{
	float invM = 1 / Module();
	x *= invM;
	y *= invM;
	z *= invM;
	w = 1;
}

Vector3d & Vector3d::ProductMatrix(const Matrix & m)
{
	x = x*m.Get(0, 0) + y*m.Get(1,0) + z*m.Get(2, 0) + w*m.Get(3,0);
	y = x*m.Get(0, 1) + y*m.Get(1,1) + z*m.Get(2, 1) + w*m.Get(3,1);
	z = x*m.Get(0, 2) + y*m.Get(1,2) + z*m.Get(2, 2) + w*m.Get(3,2);
	w = x*m.Get(0, 3) + y*m.Get(1,3) + z*m.Get(2, 3) + w*m.Get(3,3);

	return *this;
}
