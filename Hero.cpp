#include "Hero.h"

Hero::Hero(GameSystem *owner) {
	this->owner = owner;
	sprite = Sprite("data/smile.png");
	sprite2 = Sprite("data/ball.png");
}

Particle* Hero::AddParticle(Vector2f pos, float radius)
{
	Particle* newbie = new Particle;
	newbie->pos = pos;
	newbie->prevPos = newbie->pos;
	newbie->acceleration = Vector2f(0.0f, 30.0f);
	newbie->radius = radius;
	particles.push_back(newbie);

	return newbie;
}

VolumeLink* Hero::AddVolumeLink(std::vector<Particle*> particles, float initialPressure, float atmosphericPressure)
{
	volumeLink = new VolumeLink(particles, initialPressure, atmosphericPressure);
	return volumeLink;
}

Link* Hero::AddLink(Particle* p0, Particle* p1, float stiffness, float mult)
{
	Link* newLink = new Link(p0, p1, stiffness, mult);
	links.push_back(newLink);
	return newLink;
}

void Hero::Update(float dt)
{
	for (size_t particleIndex = 0; particleIndex < particles.size(); particleIndex++)
	{
		particles[particleIndex]->Integrate(dt);

		float floorLevel = 1000;
		float wall = 1000;
		if (particles[particleIndex]->pos.y > floorLevel)
		{
			particles[particleIndex]->pos.y = floorLevel;
			particles[particleIndex]->prevPos.x = particles[particleIndex]->pos.x;
		}
		if (particles[particleIndex]->pos.y < 0)
		{
			particles[particleIndex]->pos.y = 0;
			particles[particleIndex]->prevPos.x = particles[particleIndex]->pos.x;
		}
		if (particles[particleIndex]->pos.x < 0)
		{
			particles[particleIndex]->pos.x = 0;
			particles[particleIndex]->prevPos.y = particles[particleIndex]->pos.y;
		}
		if (particles[particleIndex]->pos.x > wall)
		{
			particles[particleIndex]->pos.x = wall;
			particles[particleIndex]->prevPos.y = particles[particleIndex]->pos.y;
		}

	}

	for (size_t linkIndex = 0; linkIndex < links.size(); linkIndex++)
	{
		links[linkIndex]->Solve();
	}

	volumeLink->Solve();
}

void Hero::Push(Vector2f step) {
	for (int i = 0; i < particles.size(); i++)
		if((particles[i]->pos - particles[i]->prevPos).Length() < 1.0f)
			particles[i]->pos = particles[i]->pos + step;
}

void Hero::Draw() {
	sprite.Draw(owner->GetWindow(), particles);
	for (int i = 0; i < particles.size(); i++) {
		sprite2.Draw(owner->GetWindow(), particles[i], 0.0f, Vector2f(particles[i]->radius * 2.0f, particles[i]->radius * 2.0f));
	}
}

Particle* Hero::GetParticle(int particleIndex)
{
//	std::cout << "particle index " << particleIndex << std::endl;
//	std::cout << particles[particleIndex]->pos.x << std::endl;
	return particles[particleIndex];
}

size_t Hero::GetParticleCount()
{
	return particles.size();
}

std::vector<Particle*>& Hero::getParticleVector()
{
	return particles;
}
