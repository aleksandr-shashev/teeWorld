#ifndef PHYSICS
#define PHYSICS

//include external headers
#include <SFML/System.hpp>
#include <vector>

//include local headers
#include "defines.h"
//#include "Gish.h"
#include "vector2f.h"

//parent
class Object
{
public:
	//constructor is based on vector2f
	Object (sf::Vector2f pos)
	{
		_points.push_back (pos);
	}
	//constructor is based on vector <vector2f>
	Object (std::vector <sf::Vector2f> points) :
		_points (points)
	{ }
	
	~Object ()
	{ }

	//Object position
	std::vector <sf::Vector2f> _points;
	//Is _pos a centre of figure or not 
	bool is_center;
	//Is test point inside of object or not
	virtual bool is_inside (sf::Vector2f point) = 0;
	//this method only need to Dynamic objects
	virtual void integrate (float dt) = 0;
};

//Object->Static
class Static : public Object
{
public:
	Static (sf::Vector2f pos) :
		Object (pos)
	{ }

	Static (std::vector <sf::Vector2f> points) :
		Object (points)
	{ }
	
	~Static () 
	{ }
	
	virtual bool is_inside (sf::Vector2f point) = 0;
	//In Static object we don't use integrate method
	void integrate (float dt) { };
};

//Object->Static->Rectangle
class Rectangle : public Static
{
public:
	Rectangle (std::vector <sf::Vector2f> points) :
		Static (points)
	{ }
	~Rectangle ();

	bool is_inside (sf::Vector2f point)
	{
		return false;
	}
};

//Object->Dymanic
class Dynamic : public Object
{
public:
	Dynamic (sf::Vector2f pos) :
		Object (pos)
	{ }

	Dynamic (std::vector <sf::Vector2f> points) :
		Object (points)
	{ }
	~Dynamic ()
	{ }
	
	virtual bool is_inside (sf::Vector2f point) = 0;
	virtual void integrate (float dt) = 0;
};

//Object->Dymanic->Hero
class Hero : public Dynamic
{
	float _radius;
	
public:
	Hero (sf::Vector2f pos) :
		Dynamic (pos)
	{ }
	Hero (std::vector <sf::Vector2f> points, float radius) :
		Dynamic (points),
		_radius (_radius)
	{ }
	
	~Hero ()
	{ }
	
	bool is_inside (sf::Vector2f point)
	{
		return false;
	}
	
	void integrate (float dt)
	{ }
};


//class-container
class ParticleSystem
{
	std::vector <std::vector <Object*> > objectArrays;

	//ObjectTypes types;
public:
	ParticleSystem ()
	{ }

	Object* addObject (Object* candidate, ObjectTypes type)
	{
		std::cout << "new object" << std::endl;
		if (objectArrays.size () < (int)type)
		{
			for (int i = objectArrays.size () - 1; i < (int)type; i++)
			{
				objectArrays.push_back (std::vector <Object*> ());
				std::cout << "added new vector" << std::endl;
			}
		}
		std::cout << "added new object" << std::endl;
		objectArrays [(int)type].push_back (candidate);

		return objectArrays [(int)type].back ();
	}
	void	update ()
	{ }

	Object* getObject (ObjectTypes type, int pos)
	{
		if ((int)type < objectArrays.size () && pos < objectArrays [(int)type].size ())
			return objectArrays [(int)type] [pos];
		return NULL;
	}
};


#endif // !PHYSICS