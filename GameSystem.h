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

private:
	std::vector <std::vector <Object*> > objectArrays;
	sf::RenderWindow *wnd;
};