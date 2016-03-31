#ifndef PHYSICS
#define PHYSICS

//include external headers
#include <SFML/System.hpp>
#include <vector>

//include local headers
#include "defines.h"
//#include "Gish.h"
#include "vector2f.h"
#include "particle.h"


//parent
class Object
{
public:
	Object ()
	{ }

	~Object ()
	{ }

	//Object position
	std::vector <Particle*> _particles;
	//Is _pos a centre of figure or not 
	bool is_center;
	//Is test point inside of object or not
	virtual bool is_inside (Vector2f point) = 0;
	//this method only need to Dynamic objects
	virtual void integrate (float dt) = 0;

	Particle* addParticle (Vector2f pos, float radius)
	{
		Particle* newbie = new Particle;
		newbie->pos = pos;
		newbie->prevPos = newbie->pos;
		newbie->acceleration = Vector2f (0.0f, 10.0f);
		newbie->radius = radius;
		_particles.push_back (newbie);

		return newbie;
	}
};

//Object->Static
class Static : public Object
{
public:
	Static ()
	{ }

	~Static () 
	{ }
	
	virtual bool is_inside (Vector2f point) = 0;
	//In Static object we don't use integrate method
	void integrate (float dt) { };
};

//Object->Static->Rectangle
class Rectangle : public Static
{
public:
	Rectangle ()
	{ }
	~Rectangle ()
	{ }

	bool is_inside (Vector2f point)
	{
		return false;
	}
};

//Object->Dymanic
class Dynamic : public Object
{
public:
	Dynamic ()
	{ }
	
	~Dynamic ()
	{ }
	
	virtual bool is_inside (Vector2f point) = 0;
	virtual void integrate (float dt) = 0;
};

//Object->Dymanic->Hero
class Hero : public Dynamic
{
	float step = 0.04f;
	std::vector<Link*> links;
	VolumeLink* volumeLink;

public:
	Hero ()
	{ }

	~Hero ()
	{ }
	
	bool is_inside (Vector2f point)
	{
		return false;
	}

	VolumeLink* AddVolumeLink (std::vector<Particle*> particles)
	{
		volumeLink = new VolumeLink (particles);
		return volumeLink;
	}

	Link* AddLink (Particle* p0, Particle* p1, float stiffness, float mult)
	{
		Link* newLink = new Link (p0, p1, stiffness, mult);

		links.push_back (newLink);
		return newLink;
	}

	void integrate (float dt)
	{
		for (size_t particleIndex = 0;
		particleIndex < _particles.size (); particleIndex++)
		{
			_particles [particleIndex]->Integrate (1e-2f);

			float floorLevel = 1700;
			float wall = 2000;
			if (_particles [particleIndex]->pos.y > floorLevel)
			{
				_particles [particleIndex]->pos.y = floorLevel;
				_particles [particleIndex]->prevPos.x = _particles [particleIndex]->pos.x;
			}
			if (_particles [particleIndex]->pos.y < 0)
			{
				_particles [particleIndex]->pos.y = 0;
				_particles [particleIndex]->prevPos.x = _particles [particleIndex]->pos.x;
			}
			if (_particles [particleIndex]->pos.x < 0)
			{
				_particles [particleIndex]->pos.x = 0;
				_particles [particleIndex]->prevPos.y = _particles [particleIndex]->pos.y;
			}
			if (_particles [particleIndex]->pos.x > wall)
			{
				_particles [particleIndex]->pos.x = wall;
				_particles [particleIndex]->prevPos.y = _particles [particleIndex]->pos.y;
			}

		}

		for (size_t linkIndex = 0;
		linkIndex < links.size (); linkIndex++)
		{
			links [linkIndex]->Solve ();
		}

		volumeLink->Solve ();
	}

	void Right ()
	{
		for (int i = 0; i < _particles.size (); i++)
			_particles [i]->pos = _particles [i]->pos + Vector2f (step, 0.0f);
	}
	void Left ()
	{
		for (int i = 0; i < _particles.size (); i++)
			_particles [i]->pos = _particles [i]->pos + Vector2f (-step, 0.0f);
	}
	void Up ()
	{
		for (int i = 0; i < _particles.size (); i++)
			_particles [i]->pos = _particles [i]->pos + Vector2f (0.0f, -step);
	}
	void Down ()
	{
		for (int i = 0; i < _particles.size (); i++)
			_particles [i]->pos = _particles [i]->pos + Vector2f (0.0f, step);
	}
	Particle* GetParticle (int particleIndex)
	{
		return _particles [particleIndex];
	}

	size_t GetParticleCount ()
	{
		return _particles.size ();
	}
	std::vector<Particle*>& getParticleVector ()
	{
		return _particles;
	}
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