#include "Model.h"
#include "Camera.h"

Model::Model()
{
	m_world.Unit();
}


Model::~Model()
{
	for (auto const &v : m_vertices) {
		delete v;
	}
	for (auto const &t : m_triangles) {
		delete t;
	}
}

void Model::AddVertex(Vector3d pos, Color c, TexturePos tp)
{
	Vertex *pv = new Vertex;
	pv->pos = pos;
	pv->c = c;
	pv->t = tp;

	m_vertices.push_back(pv);
}

void Model::AddTriangle(int v1, int v2, int v3)
{
	Triangle *pt = new Triangle;
	pt->vIndex[0] = v1;
	pt->vIndex[1] = v2;
	pt->vIndex[2] = v3;

	Vector3d edge1 = m_vertices[v2]->pos - m_vertices[v1]->pos;
	Vector3d edge2 = m_vertices[v3]->pos - m_vertices[v2]->pos;
	pt->norm = Vector3d::CrossProduct(edge1, edge2);

	m_triangles.push_back(pt);
}

void Model::TransformVertex(Vertex & v)
{
	m_final.TransformVector(v.pos);
}

void Model::UpdateFinal()
{
	m_final.Unit();
	m_final.TransformByOther(m_world);
	m_final.TransformByOther(g_Camera.m_cameraTrans);
	m_final.TransformByOther(g_Camera.m_projTrans);

	g_Camera.m_cameraTrans.m.Print();
	m_final.m.Print();
}

Model g_model;