#pragma once
#include "GraphDef.h"
class VertexBreaker
{
public:
	VertexBreaker(const Vertex &v1, const Vertex &v2, float step);
	~VertexBreaker();

	void Add();
	void GetPoint(Vertex &v);

	Vertex  m_invStep;
	Vertex  m_invCurr;
};

