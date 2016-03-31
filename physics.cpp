# include "physics.h"

//parent
Object::Object ()
{ }

Object::~Object ()
{
	for (int i = 0; i < _particles.size (); i++)
		delete _particles [i];
}


Particle* Object::addParticle (Vector2f pos, float radius)
{
	Particle* newbie = new Particle;
	newbie->pos = pos;
	newbie->prevPos = newbie->pos;
	newbie->acceleration = Vector2f (0.0f, 10.0f);
	newbie->radius = radius;
	_particles.push_back (newbie);

	return newbie;
}

//=============================================================================
//Object->Rectangle
Rectangle::Rectangle () :
	Object ()
{ 
	is_static = true;
}
Rectangle::~Rectangle ()
{ }

bool Rectangle::is_inside (Vector2f point)
{
	return false;
}

void Rectangle::Update ()
{ }
//=============================================================================
//Object->Hero
Hero::Hero ()
{ }

Hero::~Hero ()
{ }

bool Hero::is_inside (Vector2f point)
{
	return false;
}

VolumeLink* Hero::AddVolumeLink (std::vector<Particle*> particles)
{
	volumeLink = new VolumeLink (particles);
	return volumeLink;
}

Link* Hero::AddLink (Particle* p0, Particle* p1, float stiffness, float mult)
{
	Link* newLink = new Link (p0, p1, stiffness, mult);

	links.push_back (newLink);
	return newLink;
}

void Hero::integrate (float dt)
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

void Hero::Right ()
{
	for (int i = 0; i < _particles.size (); i++)
		_particles [i]->pos = _particles [i]->pos + Vector2f (step, 0.0f);
}
void Hero::Left ()
{
	for (int i = 0; i < _particles.size (); i++)
		_particles [i]->pos = _particles [i]->pos + Vector2f (-step, 0.0f);
}
void Hero::Up ()
{
	for (int i = 0; i < _particles.size (); i++)
		_particles [i]->pos = _particles [i]->pos + Vector2f (0.0f, -step);
}
void Hero::Down ()
{
	for (int i = 0; i < _particles.size (); i++)
		_particles [i]->pos = _particles [i]->pos + Vector2f (0.0f, step);
}
Particle* Hero::GetParticle (int particleIndex)
{
	return _particles [particleIndex];
}

size_t Hero::GetParticleCount ()
{
	return _particles.size ();
}
std::vector<Particle*>& Hero::getParticleVector ()
{
	return _particles;
}


//=============================================================================
//class-container
ParticleSystem::ParticleSystem ()
{ }

Object* ParticleSystem::addObject (Object* candidate, ObjectTypes type)
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
void ParticleSystem::update ()
{ }

Object* ParticleSystem::getObject (ObjectTypes type, int pos)
{
	if ((int)type < objectArrays.size () && pos < objectArrays [(int)type].size ())
		return objectArrays [(int)type] [pos];
	return NULL;
}