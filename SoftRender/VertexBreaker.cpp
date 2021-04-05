#include "VertexBreaker.h"


VertexBreaker::VertexBreaker(const Vertex & v1, const Vertex & v2, float step)
{
	//起始点
	float invW1 = 1 / v1.pos.w;
	m_invCurr = v1;
	m_invCurr.pos.w = invW1;

	m_invCurr.c.r *= invW1;
	m_invCurr.c.g *= invW1;
	m_invCurr.c.b *= invW1;

	m_invCurr.t.u *= invW1;
	m_invCurr.t.v *= invW1;

	m_invCurr.norm.x *= invW1;
	m_invCurr.norm.y *= invW1;
	m_invCurr.norm.z *= invW1;

	//步长
	float invW2 = 1 / v2.pos.w;
	m_invStep.pos.x = (v2.pos.x - m_invCurr.pos.x) * step;
	m_invStep.pos.y = (v2.pos.y - m_invCurr.pos.y) * step;
	m_invStep.pos.z = (v2.pos.z - m_invCurr.pos.z) * step;
	m_invStep.pos.w = (invW2 - invW1) * step;

	m_invStep.c.r = (v2.c.r * invW2 - m_invCurr.c.r) * step;
	m_invStep.c.g = (v2.c.r * invW2 - m_invCurr.c.g) * step;
	m_invStep.c.b = (v2.c.r * invW2 - m_invCurr.c.b) * step;

	m_invStep.t.u = (v2.t.u * invW2 - m_invCurr.t.u) * step;
	m_invStep.t.v = (v2.t.v * invW2 - m_invCurr.t.v) * step;

	m_invStep.norm.x = (v2.norm.x * invW2 - m_invCurr.norm.x) * step;
	m_invStep.norm.y = (v2.norm.y * invW2 - m_invCurr.norm.y) * step;
	m_invStep.norm.z = (v2.norm.z * invW2 - m_invCurr.norm.z) * step;
}

VertexBreaker::~VertexBreaker()
{
}

void VertexBreaker::Add()
{
	m_invCurr.pos.x += m_invStep.pos.x;
	m_invCurr.pos.y += m_invStep.pos.y;
	m_invCurr.pos.z += m_invStep.pos.z;
	m_invCurr.pos.w += m_invStep.pos.w;

	m_invCurr.c.r += m_invStep.c.r;
	m_invCurr.c.g += m_invStep.c.g;
	m_invCurr.c.b += m_invStep.c.b;

	m_invCurr.t.u += m_invStep.t.u;
	m_invCurr.t.v += m_invStep.t.v;

	m_invCurr.norm.x += m_invStep.norm.x;
	m_invCurr.norm.y += m_invStep.norm.y;
	m_invCurr.norm.z += m_invStep.norm.z;
}

void VertexBreaker::GetPoint(Vertex & v)
{
	v.pos.x = m_invCurr.pos.x;
	v.pos.y = m_invCurr.pos.y;
	v.pos.z = m_invCurr.pos.z;

	v.pos.w = 1 / m_invCurr.pos.w;
	float w = v.pos.w;

	v.c.r = m_invCurr.c.r * w;
	v.c.g = m_invCurr.c.g * w;
	v.c.b = m_invCurr.c.b * w;

	v.t.u = m_invCurr.t.u * w;
	v.t.v = m_invCurr.t.v * w;

	v.norm.x = m_invCurr.norm.x * w;
	v.norm.y = m_invCurr.norm.y * w;
	v.norm.z = m_invCurr.norm.z * w;
}
