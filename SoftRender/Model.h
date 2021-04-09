#ifndef MODEL_H
#define MODEL_H

#include "GraphDef.h"
#include "Transport.h"
#include <vector>
class Model
{
public:
	Model();
	~Model();

	void AddVertex(Vector3d pos, Color c, TexturePos tp);
	void AddTriangle(int v1, int v2, int v3);

	const Vertex &GetVertex(int index) { return *m_vertices[index]; }

	void TransformVertex(Vertex &v);

	std::vector<Vertex *>	m_vertices;
	std::vector<Triangle *> m_triangles;

	void UpdateFinal();

	Transport m_world;
	Transport m_final;
};

extern Model g_model;

#endif // !MODEL_H

