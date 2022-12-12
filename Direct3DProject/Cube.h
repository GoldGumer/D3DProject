#pragma once

#include <directxmath.h>

using namespace DirectX;

class Cube
{
public:
	Cube(float _position[3] = new float[3] {0.0f, 0.0f, 0.0f}, float _rotation[3] = new float[3] {0.0f, 0.0f, 0.0f}, float _scale[3] = new float[3] {1.0f, 1.0f, 1.0f});
	void Transform(float _position[3] = new float[3] {0.0f, 0.0f, 0.0f}, float _rotation[3] = new float[3] {0.0f, 0.0f, 0.0f}, float _scale[3] = new float[3] { 0.0f, 0.0f, 0.0f });
	void Translate(float _position[3] = new float[3] {0.0f, 0.0f, 0.0f});
	void Rotate(float _rotation[3] = new float[3] {0.0f, 0.0f, 0.0f});
	void ScaleUp(float _scale[3] = new float[3] {0.0f, 0.0f, 0.0f});
	XMMATRIX GetWorld();
	float* GetPosition();
	float* GetRotation();
	float* GetScale();
private:
	float position[3];
	float rotation[3];
	float scale[3];
	XMMATRIX world;
};

