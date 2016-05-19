#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Defines.h"
#include "Vector2f.h"
#include "Particle.h"

class Hero;
class Rectangle;
class Spike;
class Background;

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
	Object *AddObject (Data_T *candidate)
	{
	}
	
	template <>
	Object *AddObject (Hero *candidate)
	{
		objectsArray.push_back ((Object*)candidate);

		heroesArray.push_back (candidate);
		return objectsArray.back ();
	}

	template <>
	Object *AddObject (Rectangle *candidate)
	{
		objectsArray.push_back ((Object*)candidate);

		rectanglesArray.push_back (candidate);
		return objectsArray.back ();
	}

	template <>
	Object *AddObject (Spike *candidate)
	{
		objectsArray.push_back ((Object*)candidate);

		spikesArray.push_back (candidate);
		return objectsArray.back ();
	}
	template <>
	Object *AddObject (Background* candidate)
	{
		objectsArray.push_back ((Object*)candidate);
		backgroundsArray.push_back (candidate);
		return objectsArray.back ();
	}


	template <class Data_T> 
	Data_T *GetObject (int pos)
	{
	}

	template <>
	Hero *GetObject (int pos)
	{
		if (heroesArray.size () > pos)
			return heroesArray [pos];
		return NULL;
	}

	template <>
	Rectangle *GetObject (int pos)
	{
		if (rectanglesArray.size () > pos)
			return rectanglesArray [pos];
		return NULL;
	}
	
	template <>
	Spike *GetObject (int pos)
	{
		if (spikesArray.size () > pos)
			return spikesArray [pos];
		return NULL;
	}

	template <>
	Background *GetObject (int pos)
	{
		if (backgroundsArray.size () > pos)
			return backgroundsArray [pos];
		return NULL;
	}

	
	sf::RenderWindow *GetWindow();
	bool GameSystem::CanJump(int hero);
	void GameSystem::CreateHero();

private:
	std::vector <Object *> objectsArray;
	std::vector <Hero *> heroesArray;
	std::vector <Rectangle *> rectanglesArray;
	std::vector <Spike *> spikesArray;
	std::vector <Background *> backgroundsArray;
	//Particle 
	sf::RenderWindow *wnd;

	template <class Data_T>
	void GarbageCollector (Data_T& array)
	{
		for (int i = 0; i < array.size ();)
		{
			if (array [i])
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
			else
				break;
		}
	}

	void HandleRectangles ();
	void HandleSpikes ();

};
