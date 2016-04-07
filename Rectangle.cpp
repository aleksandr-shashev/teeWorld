#include "Rectangle.h"

Rectangle::Rectangle(GameSystem *owner, Particle* particle, float ang, Vector2f size) {
	this->owner = owner;
	this->particle = particle;
	this->ang = ang;
	this->size = size;
	sprite = Sprite("data/wall.jpg");
}

void Rectangle::Update(float dt)
{ }

void Rectangle::Draw() {
	sprite.Draw(owner->GetWindow(), particle, this->ang, this->size);
}

size_t Rectangle::GetParticleCount ()
{
	return 4;
}

Particle* Rectangle::GetParticle (int particleIndex)
{
	Vector2f xVector = Vector2f (cosf (ang), sinf (ang));
	Vector2f yVector = xVector.GetPerp ();

	Particle* newbie = new Particle;
	// newbie->pos = pos;
	newbie->prevPos = newbie->pos;
	newbie->acceleration = Vector2f (0.0f, 0.0f);
	newbie->radius = 2.0f;

	switch (particleIndex)
	{
		case 0:
		{
			Vector2f pos = particle->pos - xVector * size.x - yVector * size.y;
			newbie->pos = Vector2f (pos.x, pos.y);

			break;
		}
		case 1:
		{
			Vector2f pos = particle->pos + xVector * size.x - yVector * size.y;
			newbie->pos = Vector2f (pos.x, pos.y);

			break;
		}
		case 2:
		{
			Vector2f pos = particle->pos + xVector * size.x + yVector * size.y;
			newbie->pos = Vector2f (pos.x, pos.y);

			break;
		}
		case 3:
		{
			Vector2f pos = particle->pos - xVector * size.x + yVector * size.y;
			newbie->pos = Vector2f (pos.x, pos.y);

			break;
		}
		default: break;
	}

	return newbie;
}