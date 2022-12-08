#pragma once
#include <directxmath.h>

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	DirectX::XMFLOAT3 Pos;
};

