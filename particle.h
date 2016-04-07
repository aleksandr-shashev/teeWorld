#pragma once

#include "vector2f.h"
#include <vector>
#include <math.h>
//#include <iostream>

class Particle
{
public:
	Particle() {}
	Particle(Vector2f pos) {
		this->pos = pos;
	}
	void Integrate (float dt) {
		Vector2f currPos = pos;
		pos = pos + (pos - prevPos) + acceleration * dt * dt;
		prevPos = currPos;
	}
	float radius;
	Vector2f pos;
	Vector2f prevPos;
	Vector2f acceleration;
};

//=============================================================================
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

//=============================================================================
class VolumeLink
{
public:
	VolumeLink ()
	{ }

	VolumeLink (std::vector<Particle*> particles, 
				float initialPressure = 0.1f, 
				float atmosphericPressure = 0.1f) :
		particlesTop (particles),
		initialPressure (initialPressure),
		initialVolume (calcVolume ()),
		atmosphericPressure (atmosphericPressure)
	{ }

	void Solve ()
	{
		float currVolume = calcVolume ();
		float pressureDiff = initialPressure * initialVolume / currVolume - atmosphericPressure;

		//if (-1e-3f < pressureDiff && pressureDiff < 1e-3f)
		//pressureDiff = 0;

		for (size_t i = 0; i < particlesTop.size (); i++)
		{
			Vector2f delta = particlesTop [(i + 1) % particlesTop.size ()]->pos - particlesTop [i]->pos;
			Vector2f force = Vector2f (-delta.y, delta.x) * pressureDiff; //перпендикул¤р к ребру, помноженный на разницу давлений

			particlesTop [(i + 1) % particlesTop.size ()]->pos = particlesTop [(i + 1) % particlesTop.size ()]->pos - force;
			particlesTop [i]->pos = particlesTop [i]->pos - force;
		}
	}

	float calcVolume ()
	{
		float volume = 0;

		for (size_t i = 0; i < particlesTop.size (); i++)
			volume += particlesTop [(i + 1) % particlesTop.size ()]->pos ^ particlesTop [i]->pos * 0.5f; //векторное произведение
		return volume;
	}

private:
	std::vector<Particle*> particlesTop;
	float initialPressure;
	float initialVolume;
	float atmosphericPressure;
};