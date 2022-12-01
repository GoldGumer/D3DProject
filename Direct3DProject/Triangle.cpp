#include "Triangle.h"

Triangle::Triangle(Vertex* vertices[3])
{
	this->vertices[0] = vertices[0];
	this->vertices[1] = vertices[1];
	this->vertices[2] = vertices[2];
}

Triangle::~Triangle()
{
	for (int i = 0; i < 3; i++)
	{
		vertices[i] = nullptr;
		delete vertices[i];
	}
}

Vertex** Triangle::GetVertices()
{
	return vertices;
}
