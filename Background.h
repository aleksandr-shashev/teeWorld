#pragma once

#include "Rectangle.h"

class Background : public Rectangle
{
public:
	Background (GameSystem *owner,
		   Vector2f centre,
		   float ang,
		   Vector2f size);
	~Background () { }
};