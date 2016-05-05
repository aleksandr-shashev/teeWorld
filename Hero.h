#pragma once

#include "GameSystem.h"
#include "Sprite.h"
#include "SFML\Graphics.hpp"

class Object;

class Hero : public Object
{
public:
	Hero() {};
	Hero(GameSystem *owner);
	~Hero() {};
	Particle* AddParticle(Vector2f pos, float radius);
	Link* AddLink(Particle* p0, Particle* p1, float stiffness, float mult);
	VolumeLink* AddVolumeLink(std::vector<Particle*> particles, float initialPressure = 0.1f, float atmosphericPressure = 0.1f);
	void Update(float dt);
	void Draw();
	bool Exist () { return exist; }
	void Kill () { exist = false; }

	void Push(Vector2f step);
	Particle* GetParticle(int particleIndex);
	size_t GetParticleCount();
	std::vector<Particle*>& getParticleVector();

private:
	std::vector <Particle*> particles; //Object position
	std::vector <Link*> links;
	VolumeLink* volumeLink;
	Sprite sprite;
	Sprite sprite2;
	GameSystem *owner;
	bool exist;
};