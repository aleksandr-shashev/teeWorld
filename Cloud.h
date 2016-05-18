#pragma once

#include "Rectangle.h"

class Cloud : public Rectangle
{
public:
	Cloud (GameSystem *owner,
		   Vector2f centre,
		   float ang,
		   Vector2f size,
		   std::string fileName,
		   float speed);
	void Update(float dt);
	~Cloud () { }
private:
	float speed;
};