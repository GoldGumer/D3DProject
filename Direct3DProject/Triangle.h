#pragma once

#include "Vertex.h"

class Triangle
{
public:
	Triangle(Vertex* vertices[3]);
	~Triangle();
	Vertex** GetVertices();
private:
	//triangles always have 3 vertices so this is just an array of vertex pointers of length 3
	Vertex* vertices[3];
};

