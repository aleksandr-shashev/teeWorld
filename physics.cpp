#include "SFML\Graphics.hpp"

#include "physics.h"

//parents
Object::Object (sf::Vector2f pos)
{
	_points.push_back (pos);
}
	
Object::Object (std::vector <sf::Vector2f> points) :
	_points (points)
{ }

//=============================================================================
//Object->Static
Static::Static (sf::Vector2f pos):
	Object (pos)
{ }

Static::Static (std::vector <sf::Vector2f> points) :
	Object (points)
{ }
//=============================================================================
//Object->Static->Rectangle

Rectangle::Rectangle (std::vector <sf::Vector2f> points) :
	Static (points)
{ }

Rectangle::~Rectangle ()
{ }

bool Rectangle::is_inside (sf::Vector2f point)
{
	return false;
}

//=============================================================================
//Object->Dymanic
Dynamic::Dynamic (sf::Vector2f pos) :
	Object (pos)
{ }
	
Dynamic::Dynamic (std::vector <sf::Vector2f> points) :
	Object (points)
{ }

//=============================================================================
//Object->Dymanic->Hero
Hero::Hero (sf::Vector2f pos) :
	Dynamic (pos)
{ }

Hero::Hero (std::vector <sf::Vector2f> points, float radius) :
	Dynamic (points),
	_radius (_radius)
{ 
}

Hero::~Hero ()
{ }

bool Hero::is_inside (sf::Vector2f point)
{
	return false;
}

void Hero::integrate (float dt)
{
}
//=============================================================================
//class-container
ParticleSystem::ParticleSystem ()
{ }

Object* ParticleSystem::addObject (Object* candidate, ObjectTypes type)
{ 
	if (objectArrays.size () < (int)type)
	{
		std::vector <Object*> x;
		objectArrays.push_back (x);
	}
	objectArrays [(int)type].push_back (candidate);

	return objectArrays [(int)type].back ();
}

void ParticleSystem::update ()
{ }