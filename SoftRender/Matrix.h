#ifndef MATRIX_T_H
#define MATRIX_T_H

#include <initializer_list>
class Matrix
{
public:
	Matrix(int line, int column);
	~Matrix();
	Matrix(Matrix &&m);
	Matrix &operator=(Matrix &&m);

	void Init(const std::initializer_list<float> &initList);

	void Zero();
	void Unit();

	static Matrix Product(const Matrix &m1, const Matrix &m2);

	float Get(int i, int j) const { return m_data[i*m_column + j]; }
	void Set(int i, int j, float v) { m_data[i*m_column + j] = v; }

	void Print()const;

private:
	void Alloc()
	{
		m_data = new float[m_line * m_column];
	}
	void Release()
	{
		if (m_data != nullptr) {
			delete[]m_data;
			m_data = nullptr;
		}
	}
	Matrix(const Matrix&) = delete;
	Matrix &operator=(const Matrix&) = delete;

private:
	int m_line;
	int m_column;
	float *m_data;
};

#endif