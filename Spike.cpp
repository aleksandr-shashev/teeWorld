#include "Spike.h"

Spike::Spike (GameSystem *owner,
			  Vector2f centre,
			  float ang,
			  Vector2f size) :
	Rectangle (owner, centre, ang, size, std::string ("data/spike.png"))
{
}