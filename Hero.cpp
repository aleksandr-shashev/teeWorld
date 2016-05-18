#include "Hero.h"

Hero::Hero(GameSystem *owner, Vector2f pos, int particleAmount) {
	int count = particleAmount;
	float pi = 3.1415926f;
	Vector2f circleCenter = pos;
	this->AddCenter(circleCenter, 5.0f, Vector2f(0.0f, 50.0f));
	float circleRadius = 25;
	for (int i = 0; i < count; i++) {
		float ang = float(i) / count * (2.0f * pi);
		Vector2f pos = Vector2f(cosf(ang), sinf(ang)) * circleRadius + circleCenter;
		AddParticle(pos, 1.0f, Vector2f(0.0f, 0.0f));
	}
	for (int i = 0; i < count; i++) {
		AddLink(GetParticle(i), GetParticle((i + 1) % count), 0.05f, 1.0f);
	}
	for (int i = 0; i < count; i++) {
		AddLink(GetParticle(i), GetParticle((i + count / 2) % count), 0.05f, 1.0f);
	}
	for (int i = 0; i < count; i++) {
		AddLink(GetParticle(i), GetCenter(), 0.05f, 1.0f);
	}


	this->owner = owner;
	sprite = Sprite("data/smile.png");
	sprite2 = Sprite("data/ball.png");
	exist = true;
}

Particle* Hero::AddParticle(Vector2f pos, float radius, Vector2f acceleration)
{
	Particle* newbie = new Particle;
	newbie->pos = pos;
	newbie->prevPos = newbie->pos;
	newbie->acceleration = acceleration;
	newbie->radius = radius;
	particles.push_back(newbie);

	return newbie;
}

Particle* Hero::AddCenter(Vector2f pos, float radius, Vector2f acceleration)
{
	Particle* newbie = new Particle;
	newbie->pos = pos;
	newbie->prevPos = newbie->pos;
	newbie->acceleration = acceleration;
	newbie->radius = radius;
	center = newbie;

	return center;
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
		center->Integrate(dt);

		if (particles[particleIndex]->pos.y > owner->GetGameSize().y)
		{
			particles[particleIndex]->pos.y = owner->GetGameSize().y;
			particles[particleIndex]->prevPos.x = particles[particleIndex]->pos.x;
			center->prevPos = center->pos;
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
		if (particles[particleIndex]->pos.x > owner->GetGameSize().x)
		{
			particles[particleIndex]->pos.x = owner->GetGameSize().x;
			particles[particleIndex]->prevPos.y = particles[particleIndex]->pos.y;
		}

	}

	for (size_t linkIndex = 0; linkIndex < links.size(); linkIndex++)
	{
		links[linkIndex]->Solve();
	}

}

void Hero::Push(Vector2f step) {
	if ((center->pos - center->prevPos).Length() < 0.5f)
		center->pos = center->pos + step;
	for (int i = 0; i < particles.size(); i++)
		if((particles[i]->pos - particles[i]->prevPos).Length() < 0.5f)
			particles[i]->pos = particles[i]->pos + step;
	
}

void Hero::Draw() {
	sprite.DrawWorldspace(owner->GetWindow(), particles, owner->cam);
	for (int i = 0; i < particles.size(); i++) {
		//sprite2.DrawWorldspace(owner->GetWindow(), particles[i]->pos, 0.0f, Vector2f(particles[i]->radius * 2.0f, particles[i]->radius * 2.0f), owner->cam);
	}
}

Particle* Hero::GetParticle(int particleIndex)
{
//	std::cout << "particle index " << particleIndex << std::endl;
//	std::cout << particles[particleIndex]->pos.x << std::endl;
	return particles[particleIndex];
}

Particle* Hero::GetCenter()
{
	//	std::cout << "particle index " << particleIndex << std::endl;
	//	std::cout << particles[particleIndex]->pos.x << std::endl;
	return center;
}

size_t Hero::GetParticleCount()
{
	return particles.size();
}

std::vector<Particle*>& Hero::getParticleVector()
{
	return particles;
}
