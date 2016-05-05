#include "Background.h"

Background::Background (GameSystem *owner,
						Vector2f centre,
						float ang,
						Vector2f size) :
	Rectangle (owner, centre, ang, size, std::string ("data/background.jpg"))
{ }