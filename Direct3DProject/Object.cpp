#include "Object.h"

Object::Object(float _position[3], float _rotation[3], float _scale[3])
{
	world = XMMatrixIdentity();
	for (int i = 0; i < 3; i++)
	{
		position[i] = _position[i];
		rotation[i] = _rotation[i];
		scale[i] = _scale[i];
	}
	Transform();
}

void Object::Transform(float _position[3], float _rotation[3], float _scale[3])
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

void Object::Translate(float _position[3])
{
	Transform(_position);
}

void Object::Rotate(float _rotation[3])
{
	Transform(new float[3] {0.0f, 0.0f, 0.0f}, _rotation);
}

void Object::ScaleUp(float _scale[3])
{
	Transform(new float[3] {0.0f, 0.0f, 0.0f}, new float[3] {0.0f, 0.0f, 0.0f}, _scale);
}

XMMATRIX Object::GetWorld()
{
	return world;
}

float* Object::GetPosition()
{
	return position;
}

float* Object::GetRotation()
{
	return rotation;
}

float* Object::GetScale()
{
	return scale;
}