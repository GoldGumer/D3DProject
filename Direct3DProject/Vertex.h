#pragma once
class Vertex
{
public:
	Vertex(float x, float y, float z);
	float* GetPos();
private:
	float x, y, z;
};

