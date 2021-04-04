#include "Model.h"



Model::Model()
{
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
