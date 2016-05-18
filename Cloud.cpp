#include "Cloud.h"

Cloud::Cloud (GameSystem *owner,
			  Vector2f centre,
			  float ang,
			  Vector2f size,
			  std::string fileName,
			  float speed) :
	Rectangle (owner, centre, ang, size, fileName)
{
	this->speed = speed;
}

void Cloud::Update(float dt) {
	centre.x = centre.x - speed * dt;
	if (centre.x < -200.0f )
		centre.x = owner->GetGameSize().x + 200.0f;
}