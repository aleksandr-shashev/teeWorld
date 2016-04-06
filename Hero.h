#include "GameSystem.h"
#include "Sprite.h"
#include "SFML\Graphics.hpp"

class Hero : public Object
{
public:
	Hero() {};
	Hero(GameSystem *owner);
	~Hero() {};
	Particle* AddParticle(Vector2f pos, float radius);
	Link* AddLink(Particle* p0, Particle* p1, float stiffness, float mult);
	VolumeLink* AddVolumeLink(std::vector<Particle*> particles);
	void Update(float dt);
	void Draw();

	Particle* GetParticle(int particleIndex);
	size_t GetParticleCount();
	std::vector<Particle*>& getParticleVector();

private:
	float step = 0.01f;
	std::vector <Particle*> particles; //Object position
	std::vector <Link*> links;
	VolumeLink* volumeLink;
	Sprite sprite;
	GameSystem *owner;
};