#include "Vertex.h"

Vertex::Vertex()
{
	x = 0;
	y = 0;
	z = 0;
}

Vertex::Vertex(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float* Vertex::GetPos()
{
	return new float[3] {x, y, z};
}
