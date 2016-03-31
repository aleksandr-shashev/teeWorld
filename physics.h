#pragma once

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
	Object ();
	~Object ();

	std::vector <Particle*> _particles; //Object position
	bool is_static; //Is Object static or dynamic;
	virtual bool is_inside (Vector2f point) = 0; //Is test point inside of object or not
	virtual void integrate (float dt) = 0; //this method only need to Dynamic objects
	
	Particle* addParticle (Vector2f pos, float radius);
};


//Object->Rectangle
class Rectangle : public Object
{
public:
	Rectangle ();
	~Rectangle ();

	bool is_inside (Vector2f point);
	void Update ();
};



//Object->Hero
class Hero : public Object
{
	float step = 0.04f;
	std::vector<Link*> links;
	VolumeLink* volumeLink;

public:
	Hero ();
	~Hero ();
	
	bool is_inside (Vector2f point);

	VolumeLink* AddVolumeLink (std::vector<Particle*> particles);

	Link* AddLink (Particle* p0, Particle* p1, float stiffness, float mult);

	void integrate (float dt);

	void Right ();
	void Left ();
	void Up ();
	void Down ();
	Particle* GetParticle (int particleIndex);
	size_t GetParticleCount ();
	std::vector<Particle*>& getParticleVector ();
};


//class-container
class ParticleSystem
{
	std::vector <std::vector <Object*> > objectArrays;

	//ObjectTypes types;
public:
	ParticleSystem ();
	Object* addObject (Object* candidate, ObjectTypes type);
	void	update ();
	Object* getObject (ObjectTypes type, int pos);
};