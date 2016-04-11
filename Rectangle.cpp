#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(GameSystem *owner, Vector2f centre, float ang, Vector2f size) {
	this->owner = owner;
	this->ang = ang;
	this->centre = centre;
	this->size = size;
	sprite = Sprite("data/wall.jpg");
	sprite2 = Sprite("data/ball.png");

	Vector2f points[4];
	Vector2f pointPos;
	Vector2f xVector = Vector2f(cosf(ang), sinf(ang));
	Vector2f yVector = xVector.GetPerp();

	pointPos = centre - xVector * size.x * 0.5f - yVector * size.y * 0.5f;
	points[0] = Vector2f(pointPos.x, pointPos.y);

	pointPos = centre + xVector * size.x * 0.5f - yVector * size.y * 0.5f;
	points[1] = Vector2f(pointPos.x, pointPos.y);

	pointPos = centre + xVector * size.x * 0.5f + yVector * size.y * 0.5f;
	points[2] = Vector2f(pointPos.x, pointPos.y);

	pointPos = centre - xVector * size.x * 0.5f + yVector * size.y * 0.5f;
	points[3] = Vector2f(pointPos.x, pointPos.y);
	
	for (int i = 0; i < 4; i++) {
		//Vector2f side = (points[(i + 1) % 4] - points[i]).GetNorm();
		Vector2f pos = points[i];
		//std::cout << pos.x<< " " << pos.y << " " << side.x << " " << side.y << std::endl;

	//	while ((pos - points[(i + 1) % 4]).Length() > 6.0f) {
			Particle* newParticle = new Particle(pos, 5.0f);
			particles.push_back(newParticle);
		//	pos = pos + side * 10.0f;
		//}
	}
}

void Rectangle::Update(float dt)
{ }

void Rectangle::Draw() {
	sprite.Draw(owner->GetWindow(), centre, this->ang, this->size);
	for (int i = 0; i < particles.size(); i++) {
		sprite2.Draw(owner->GetWindow(), particles[i], 0.0f, Vector2f(particles[i]->radius * 2.0f, particles[i]->radius * 2.0f));
	}
}

size_t Rectangle::GetParticleCount ()
{
	return particles.size();
}

Particle* Rectangle::GetParticle (int particleIndex)
{
	return particles[particleIndex];
}


Vector2f Rectangle::GetMinPerp (Particle* point)
{
	Vector2f min (MAXNUMBER, MAXNUMBER);
	for (int i = 0; i < particles.size (); i++)
	{
		Particle* curRectParticle = particles [i];
		Particle* nextRectParticle = particles [(i + 1) % particles.size ()];
		Vector2f rib = nextRectParticle->pos - curRectParticle->pos;

		Vector2f delta = -rib.GetPerp ();
		Vector2f vecToPos = point->pos - curRectParticle->pos;
		float deltaScale = abs (-vecToPos ^ rib) / rib.Length ();
		delta = delta * (deltaScale);
		if (min.Length () > delta.Length ())
			min = delta;
	}
	return min;
}


bool Rectangle::IsInside (Vector2f pos)
{
	int sign = 0.0f;

	for (int i = 0; i < particles.size (); i++)
	{
		Particle* curRectParticle = particles [i];

		Particle* nextRectParticle = particles [(i + 1) % particles.size ()];

		Vector2f rib = nextRectParticle->pos - curRectParticle->pos;

		Vector2f vecToPos = pos - curRectParticle->pos;
		float deltaScale = -vecToPos ^ rib;

		if (deltaScale < 1e-5f)
			return false;
	}
	return true;
}