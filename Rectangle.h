#include "GameSystem.h"
#include "Sprite.h"

class Rectangle : public Object
{
public:
	Rectangle() {};
	Rectangle(GameSystem *owner, Vector2f centre, float ang, Vector2f size);
	~Rectangle() {};
	void Update(float dt);
	void Draw();
	size_t GetParticleCount ();
	Particle* GetParticle (int particleIndex);
	Vector2f GetMinPerp (Particle* point);
	bool IsInside (Vector2f pos);

private:
	std::vector<Particle *> particles;
	float ang;
	Vector2f centre;
	Vector2f size;
	Sprite sprite;
	Sprite sprite2;
	GameSystem *owner;
};