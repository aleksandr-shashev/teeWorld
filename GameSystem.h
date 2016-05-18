#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Defines.h"
#include "Vector2f.h"
#include "Particle.h"
#include "Sprite.h"

class Hero;
class Rectangle;
class Spike;
class Background;
class Bomb;
class Cloud;

class Object
{
public:
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual bool Exist () = 0;

	virtual size_t GetParticleCount() { return 0; };
	virtual Particle* GetParticle(int particleIndex) { return NULL; };
	virtual void Push(Vector2f step) {};
	virtual Vector2f GetMinPerp (Particle* point) { return Vector2f (0.0f, 0.0f); }
	virtual bool IsInside (Vector2f pos) { return false; }
};


class GameSystem
{
public:
	GameSystem() {};
	GameSystem(sf::RenderWindow *wnd, Vector2f gameSize);
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
	Object *AddObject(Bomb *candidate)
	{
		objectsArray.push_back((Object*)candidate);

		bombsArray.push_back(candidate);
		return objectsArray.back();
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
	Object *AddObject(Cloud *candidate)
	{
		objectsArray.push_back((Object*)candidate);

		cloudsArray.push_back(candidate);
		return objectsArray.back();
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
	Bomb *GetObject(int pos)
	{
		if (bombsArray.size() > pos)
			return bombsArray[pos];
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
	Cloud *GetObject(int pos)
	{
		if (cloudsArray.size() > pos)
			return cloudsArray[pos];
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
	bool CanJump(int hero);
	Vector2f GetGameSize();
	int GetHeroAmount();
	Camera cam;
private:
	std::vector <Object *> objectsArray;
	std::vector <Hero *> heroesArray;
	std::vector <Rectangle *> rectanglesArray;
	std::vector <Spike *> spikesArray;
	std::vector <Background *> backgroundsArray;
	std::vector <Bomb *> bombsArray;
	std::vector <Cloud *> cloudsArray;
	//Particle 
	sf::RenderWindow *wnd;
	Vector2f gameSize;

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
