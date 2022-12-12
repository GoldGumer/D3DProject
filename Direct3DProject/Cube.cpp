#include "Cube.h"

Cube::Cube(float _position[3], float _rotation[3], float _scale[3])
{
	world = XMMatrixIdentity();
	for (int i = 0; i < 3; i++)
	{
		position[i] = _position[i];
		rotation[i] = _rotation[i];
		scale[i] = _scale[i];
	}
}

void Cube::Transform(float _position[3], float _rotation[3], float _scale[3])
{
	for (int i = 0; i < 3; i++)
	{
		position[i] += _position[i];
		rotation[i] += _rotation[i];
		scale[i] += _scale[i];
	}

	XMMATRIX mTranslation = XMMatrixTranslation( position[0], position[1], position[2] );
	XMMATRIX mRotation = XMMatrixRotationRollPitchYaw( rotation[0], rotation[1], rotation[2] );
	XMMATRIX mScaling = XMMatrixScaling( scale[0], scale[1], scale[2] );

	world = mScaling * mRotation * mTranslation;
}

XMMATRIX Cube::GetWorld()
{
	return world;
}

float* Cube::GetPosition()
{
	return position;
}

float* Cube::GetRotation()
{
	return rotation;
}

float* Cube::GetScale()
{
	return scale;
}
