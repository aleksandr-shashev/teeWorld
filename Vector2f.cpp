#pragma once
#include <string>
#include "Vector2f.h"

Vector2f Add (Vector2f v0, Vector2f v1)
{
	return Vector2f (v0.x + v1.x, v0.y + v1.y);
}

Vector2f operator +(Vector2f v0, Vector2f v1)
{
	return Vector2f (v0.x + v1.x, v0.y + v1.y);
}

Vector2f operator - (Vector2f v0, Vector2f v1)
{
	return Vector2f (v0.x - v1.x, v0.y - v1.y);
}

Vector2f operator - (Vector2f v)
{
	return Vector2f (-v.x, -v.y);
}

Vector2f operator * (Vector2f v0, float param)
{
	return Vector2f (v0.x * param, v0.y * param);
}

Vector2f operator*(float param, Vector2f v1)
{
	return Vector2f (v1.x*param, v1.y*param);
}

float operator ^ (Vector2f v1, Vector2f v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}