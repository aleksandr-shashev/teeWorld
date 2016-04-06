#include "GameSystem.h"
#include "Sprite.h"

class Rectangle : public Object
{
public:
	Rectangle() {};
	Rectangle(GameSystem *owner, Particle* particle, float ang, Vector2f size);
	~Rectangle() {};
	void Update(float dt);
	void Draw();

private:
	Particle *particle;
	float ang;
	Vector2f size;
	Sprite sprite;
	GameSystem *owner;
};