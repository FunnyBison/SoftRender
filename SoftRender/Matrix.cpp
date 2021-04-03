#include "Matrix.h"
#include <assert.h>
#include <stdio.h>

Matrix::Matrix(int line, int column) 
	:m_line(line), m_column(column), m_data(nullptr)
{ 
	Alloc(); 
}

Matrix::~Matrix() 
{
	Release();
}

Matrix::Matrix(Matrix && m)
{
	Release();
	m_data = m.m_data; 
	m_line = m.m_line; 
	m_column = m.m_column; 

	m.m_data = nullptr;
}

Matrix & Matrix::operator=(Matrix && m)
{
	Release();
	m_data = m.m_data; 
	m_line = m.m_line; 
	m_column = m.m_column; 

	m.m_data = nullptr;
	return *this;
}

void Matrix::Init(const std::initializer_list<float>& initList)
{
	auto it = initList.begin();
	for (int i = 0; i < m_line; i++) {
		for (int j = 0; j < m_column; j++) {
			Set(i, j, *it);
			++it;
		}
	}
}

void Matrix::Zero()
{
	for (int i = 0; i < m_line; i++) {
		for (int j = 0; j < m_column; j++) {
			Set(i, j, 0);
		}
	}
}

void Matrix::Unit()
{
	for (int i = 0; i < m_line; i++) {
		for (int j = 0; j < m_column; j++) {
			Set(i, j, i==j ? 1.0f : 0);
		}
	}
}

Matrix Matrix::Product(const Matrix & m1, const Matrix & m2)
{
	assert(m1.m_column == m2.m_line);
	Matrix ret(m1.m_line, m2.m_column);
	for (int i = 0; i < m1.m_line; i++) {
		for (int j = 0; j < m2.m_column; j++) {
			float sum = 0;
			for (int k = 0; k < m1.m_column; k++) {
				float vij = m1.Get(i, k) * m2.Get(k, j);
				sum += vij;
			}
			ret.Set(i, j, sum);
		}
	}
	return ret;
}

void Matrix::Print()
{
	for (int i = 0; i < m_line; i++) {
		for (int j = 0; j < m_column; j++) {
			printf("%.2f\t", Get(i, j));
		}
		printf("\n");
	}
	printf("\n");
}
