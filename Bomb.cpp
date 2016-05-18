#include "Bomb.h"

Bomb::Bomb(GameSystem *owner, Vector2f pos, int particleAmount, Vector2f speed, float radius) {
	int count = particleAmount;
	float pi = 3.1415926f;
	Vector2f circleCenter = pos;
	this->AddCenter(circleCenter, 5.0f, Vector2f(0.0f, 50.0f));
	center->prevPos = circleCenter - speed;
	float circleRadius = radius;
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
	this->radius = radius;
	sprite = Sprite("data/smile.png");
	sprite2 = Sprite("data/ball.png");
	exist = true;
}

Particle* Bomb::AddParticle(Vector2f pos, float radius, Vector2f acceleration)
{
	Particle* newbie = new Particle;
	newbie->pos = pos;
	newbie->prevPos = newbie->pos;
	newbie->acceleration = acceleration;
	newbie->radius = radius;
	particles.push_back(newbie);

	return newbie;
}

Particle* Bomb::AddCenter(Vector2f pos, float radius, Vector2f acceleration)
{
	Particle* newbie = new Particle;
	newbie->pos = pos;
	newbie->prevPos = newbie->pos;
	newbie->acceleration = acceleration;
	newbie->radius = radius;
	center = newbie;

	return center;
}

VolumeLink* Bomb::AddVolumeLink(std::vector<Particle*> particles, float initialPressure, float atmosphericPressure)
{
	volumeLink = new VolumeLink(particles, initialPressure, atmosphericPressure);
	return volumeLink;
}

Link* Bomb::AddLink(Particle* p0, Particle* p1, float stiffness, float mult)
{
	Link* newLink = new Link(p0, p1, stiffness, mult);
	links.push_back(newLink);
	return newLink;
}

void Bomb::Update(float dt)
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

void Bomb::Push(Vector2f step) {
	if ((center->pos - center->prevPos).Length() < 0.5f)
		center->pos = center->pos + step;
	for (int i = 0; i < particles.size(); i++)
		if((particles[i]->pos - particles[i]->prevPos).Length() < 0.5f)
			particles[i]->pos = particles[i]->pos + step;
	
}

void Bomb::Draw() {
	sprite.DrawWorldspace(owner->GetWindow(), particles, owner->cam);
	for (int i = 0; i < particles.size(); i++) {
		sprite2.DrawWorldspace(owner->GetWindow(), particles[i]->pos, 0.0f, Vector2f(particles[i]->radius * 2.0f, particles[i]->radius * 2.0f), owner->cam);
	}
}

Particle* Bomb::GetParticle(int particleIndex)
{
//	std::cout << "particle index " << particleIndex << std::endl;
//	std::cout << particles[particleIndex]->pos.x << std::endl;
	return particles[particleIndex];
}

Particle* Bomb::GetCenter()
{
	//	std::cout << "particle index " << particleIndex << std::endl;
	//	std::cout << particles[particleIndex]->pos.x << std::endl;
	return center;
}

float Bomb::GetRadius() {
	return radius;
};

size_t Bomb::GetParticleCount()
{
	return particles.size();
}

std::vector<Particle*>& Bomb::getParticleVector()
{
	return particles;
}
