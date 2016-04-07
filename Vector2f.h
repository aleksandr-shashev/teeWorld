#pragma once

#include <iostream>
#include <string>

class Vector2f
{
public:
	Vector2f ()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2f (float _x, float _y)
	{
		x = _x;
		this->y = _y;
	}
	~Vector2f ()
	{ }

	void Print ()
	{
		std::cout <<
			"x: " << x << "\n" <<
			"y: " << y << "\n" << std::endl;
	}
	float Length ()
	{
		return sqrt (x*x + y*y);
	}

	Vector2f GetNorm ()
	{
		return Vector2f (x / Length (), y / Length ());
	}

	Vector2f GetPerp()
	{
		return Vector2f((-1)*y / Length(), x / Length());
	}

	float x, y;
};

Vector2f Add(Vector2f v0, Vector2f v1);

Vector2f operator +(Vector2f v0, Vector2f v1);

Vector2f operator - (Vector2f v0, Vector2f v1);

Vector2f operator * (Vector2f v0, float param);

Vector2f operator*(float param, Vector2f v1);

float operator ^ (Vector2f v1, Vector2f v2);