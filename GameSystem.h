#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Defines.h"
#include "Vector2f.h"
#include "Particle.h"

class Hero;
class Rectangle;

class Object
{
public:
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual bool Exist () = 0;

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

	template <class Data_T> 
	Object *AddObject (Data_T *candidate, ObjectTypes type)
	{
		objectsArray.push_back ((Object*)candidate);

		switch (type)
		{
			case HERO:
			{
				heroesArray.push_back ((Hero*)candidate);
				break;
			}
			case RECTANGLE:
			{
				rectanglesArray.push_back ((Rectangle*)candidate);
				break;
			}
			default: break;
		}

		return objectsArray.back ();
	}
	
	template <class Data_T> 
	Data_T *GetObject (ObjectTypes type, int pos)
	{
		switch (type)
		{
			case HERO:
			{
				if (heroesArray.size () > pos)
					return heroesArray [pos];
				break;
			}
			case RECTANGLE:
			{
				if (rectanglesArray.size () > pos)
					return rectanglesArray [pos];
				break;
			}
			default: break;
		}
		return NULL;
	}
	
	sf::RenderWindow *GetWindow();
	bool GameSystem::CanJump(int hero);

private:
	std::vector <Object *> objectsArray;
	std::vector <Hero *> heroesArray;
	std::vector <Rectangle *> rectanglesArray;
	//Particle 
	sf::RenderWindow *wnd;

	template <class Data_T>
	void GarbageCollector (Data_T& array)
	{
		for (int i = 0; i < array.size ();)
		{
			if (!array [i]->Exist ())
			{
				delete array [i];
				array [i] = array.back ();
				array.pop_back ();
			}
			else
				i++;
		}
	}
};

#include "Hero.h"
#include "Rectangle.h"	