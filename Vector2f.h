#pragma once

#include <iostream>
#include <string>

class Vector2f
{
public:
	Vector2f ();
	Vector2f (float _x, float _y);
	~Vector2f ();

	void Print ();
	float Length ();
	Vector2f GetNorm ();
	
	float x;
    float y;
};

Vector2f Add (Vector2f v0, Vector2f v1);

Vector2f operator + (Vector2f v0, Vector2f v1);
Vector2f operator - (Vector2f v0, Vector2f v1);
Vector2f operator * (Vector2f v0, float param);
Vector2f operator * (float param, Vector2f v1);
float 	 operator ^ (Vector2f v1, Vector2f v2);
