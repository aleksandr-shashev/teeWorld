#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Defines.h"
#include "Vector2f.h"
#include "Particle.h"

class Object
{
public:
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual size_t GetParticleCount () = 0;
	virtual Particle* GetParticle (int particleIndex) = 0;
	virtual void Push(Vector2f step) {};
	virtual Vector2f GetMinPerp (Particle* point) { return Vector2f (0.0f, 0.0f); }
	virtual bool IsInside (Vector2f pos) { return false; }
};


class GameSystem
{
public:
	GameSystem() {};
	GameSystem(sf::RenderWindow *wnd);
	void Update(float dt);
	void Draw();
	Object *AddObject (Object *candidate, ObjectTypes type);
	Object *GetObject (ObjectTypes type, int pos);
	sf::RenderWindow *GetWindow();
	bool GameSystem::CanJump(int hero);

private:
	std::vector <std::vector <Object*> > objectArrays;
	sf::RenderWindow *wnd;
};