#ifndef MODEL_H
#define MODEL_H

#include "GraphDef.h"
#include <vector>
class Model
{
public:
	Model();
	~Model();

	std::vector<Vertex *>	m_vertices;
	std::vector<Triangle *> m_triangles;
};


#endif // !MODEL_H

