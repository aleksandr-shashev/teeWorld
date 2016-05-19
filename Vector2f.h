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

	/*Vector2f GetPerpToLine (Vector2f linePoint1, Vector2f linePoint2, Vector2f point)
	{
		Vector2f rib = linePoint2 - linePoint1;

		Vector2f delta = -rib.GetPerp ();
		Vector2f vecToPos = point - linePoint1;
		float deltaScale = abs (-vecToPos ^ rib) / rib.Length ();
		delta = delta * (deltaScale);

		return delta;
	}*/

	float x, y;
};

Vector2f Add(Vector2f v0, Vector2f v1);

Vector2f operator +(Vector2f v0, Vector2f v1);

Vector2f operator - (Vector2f v0, Vector2f v1);

Vector2f operator - (Vector2f v0);

Vector2f operator * (Vector2f v0, float param);

Vector2f operator*(float param, Vector2f v1);

float operator ^ (Vector2f v1, Vector2f v2);