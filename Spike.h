#pragma once

#include "Rectangle.h"

class Spike : public Rectangle
{
public:
	Spike (GameSystem *owner,
		   Vector2f centre,
		   float ang,
		   Vector2f size);
	~Spike () { }
};