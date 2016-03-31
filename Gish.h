#include "vector2f.h"
#include <vector>
#include <math.h>
#include <iostream>

class Particle
{
public:
	void Integrate (float dt)
	{
		Vector2f currPos = pos;
		pos = pos + (pos - prevPos) + acceleration * dt * dt;
		prevPos = currPos;
	}
	float radius;
	Vector2f pos;
	Vector2f prevPos;
	Vector2f acceleration;
};

class Link
{
public:
	Link ()
	{

	}
	Link (Particle *p0, Particle *p1, float stiffness, float mult)
	{
		this->p0 = p0;
		this->p1 = p1;
		this->stiffness = stiffness;
		this->defLength = mult * (p0->pos - p1->pos).Length ();
	}
	void Solve ()
	{
		Vector2f delta = p1->pos - p0->pos;
		float deform = delta.Length () - this->defLength;
		p0->pos = p0->pos + delta.GetNorm () * deform * 0.5 * stiffness;
		p1->pos = p1->pos + delta.GetNorm () * deform * -0.5 * stiffness;

	}
	Particle *p0, *p1;
	float stiffness;
	float defLength;
};

class ParticleSystem
{
public:
	ParticleSystem()
	{
	}

	Particle* AddParticle(Vector2f pos, float radius)
	{
		Particle* newbie = new Particle;
		newbie->pos = pos;
		newbie->prevPos = newbie->pos;
		newbie->acceleration = Vector2f(0.0f, 10.0f);
		newbie->radius = radius;
		particles.push_back(newbie);

		return newbie;
	}

	

	Link* AddLink (Particle* p0, Particle* p1, float stiffness, float mult)
	{
		Link* newLink = new Link (p0, p1, stiffness, mult);

		links.push_back (newLink);
		return newLink;
	}

	void Update()
	{
		for (size_t particleIndex = 0;
			particleIndex < particles.size(); particleIndex++)
		{
			particles[particleIndex]->Integrate(1e-2f);
		
			float floorLevel = 1700;
			float wall = 2000;
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

		for (size_t linkIndex = 0;
			linkIndex < links.size(); linkIndex++)
		{
			links[linkIndex]->Solve();
		}

	}

	void Right()
	{
		for (int i = 0; i < particles.size(); i++)
			particles[i]->pos = particles[i]->pos + Vector2f(step, 0.0f);
	}
	void Left()
	{
		for (int i = 0; i < particles.size(); i++)
			particles[i]->pos = particles[i]->pos + Vector2f(-step, 0.0f);
	}
	void Up()
	{
		for (int i = 0; i < particles.size(); i++)
			particles[i]->pos = particles[i]->pos + Vector2f(0.0f, -step);
	}
	void Down()
	{
		for (int i = 0; i < particles.size(); i++)
			particles[i]->pos = particles[i]->pos + Vector2f(0.0f, step);
	}
	Particle* GetParticle(int particleIndex)
	{
		return particles[particleIndex];
	}

	size_t GetParticleCount()
	{
		return particles.size();
	}
	std::vector<Particle*>& getParticleVector ()
	{
		return particles;
	}

private:
	float step = 0.04f;
	std::vector<Particle*> particles;
	std::vector<Link*> links;
};