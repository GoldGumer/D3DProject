#include "Vertex.h"

Vertex::Vertex()
{
	Pos = DirectX::XMFLOAT3(0, 0, 0);
}

Vertex::Vertex(float x, float y, float z)
{
	Pos = DirectX::XMFLOAT3(x, y, z);
}
