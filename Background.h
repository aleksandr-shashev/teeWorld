#pragma once
#include "GameSystem.h"
#include "Sprite.h"
#include <math.h>
#include <string>

//#include "ParticleSystem.h"
class Particle; //от кольцевых зависимостей

class Background : public Object {
public:
	Background() {};
	Background(GameSystem *owner, std::string nameOfFile, float paralax);
	void Update(float dt) {};
	void Draw();
	bool Exist() { return 1; }
private:
	Sprite sprite;
	GameSystem *owner;
	float paralax;
};