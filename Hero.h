#pragma once

#include "GameSystem.h"
#include "Sprite.h"
#include "SFML\Graphics.hpp"

class Object;

class Hero : public Object
{
public:
	Hero() {};
	Hero(GameSystem *owner, Vector2f pos, int particleAmount);
	~Hero() {};
	Particle* AddParticle(Vector2f pos, float radius, Vector2f acceleration);
	Particle* AddCenter(Vector2f pos, float radius, Vector2f acceleration);
	Link* AddLink(Particle* p0, Particle* p1, float stiffness, float mult);
	VolumeLink* AddVolumeLink(std::vector<Particle*> particles, float initialPressure = 0.1f, float atmosphericPressure = 0.1f);
	void Update(float dt);
	void Draw();
	bool Exist () { return exist; }
	void Kill () { exist = false; }

	void Push(Vector2f step);
	Particle* GetParticle(int particleIndex);
	Particle* GetCenter();
	size_t GetParticleCount();
	std::vector<Particle*>& getParticleVector();
	
private:
	std::vector <Particle*> particles; //Object position
	Particle* center;
	std::vector <Link*> links;
	VolumeLink* volumeLink;
	Sprite sprite;
	Sprite sprite2;
	GameSystem *owner;
	bool exist;
};