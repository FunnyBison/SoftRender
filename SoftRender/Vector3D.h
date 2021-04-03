#pragma once

#include <initializer_list>
class Matrix;

struct Vector3d
{
	Vector3d() { w = 1; }
	Vector3d(float _x, float _y, float _z, float _w = 1.0f) { x = _x; y = _y; z = _z; w = _w; }

	Vector3d &operator = (std::initializer_list<float> initList);
	float x;
	float y;
	float z;
	float w;

	static float DotProduct(const Vector3d &v1, const Vector3d &v2);
	static Vector3d CrossProduct(const Vector3d &v1, const Vector3d &v2);
	float Module();
	void Normalize();
	Vector3d &ProductMatrix(const Matrix &m);

	friend Vector3d operator + (const Vector3d &v1, const Vector3d &v2) { return Vector3d(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z); }
	friend Vector3d operator - (const Vector3d &v1, const Vector3d &v2) { return Vector3d(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z); }

	Vector3d operator - () { return Vector3d({ -x, -y, -z }); }

	static Vector3d const Zero;
};