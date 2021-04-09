#ifndef TRANSPORT_H
#define TRANSPORT_H
#include "Matrix.h"
struct Vector3d;
class Transport
{
public:
	Transport();
	~Transport();
	Transport(Transport &&t);
	Transport &operator=(Transport &&t);
	//void TransformByMatrix(const Matrix &matrix);
	void TransformByOther(const Transport &tr);

	Transport &Unit() { m.Unit(); return *this; }

	Transport &Translate(float x, float y, float z);
	Transport &Translate(const Vector3d &tv);
	Transport &RotateX(float angle);
	Transport &RotateY(float angle);
	Transport &RotateZ(float angle);

	float Get(int i, int j) { return m.Get(i, j); }
	void Set(int i, int j, float v) { m.Set(i, j, v); }

	void TransformVector(Vector3d &v);

	Matrix m;
};

#endif // !TRANSPORT_H

