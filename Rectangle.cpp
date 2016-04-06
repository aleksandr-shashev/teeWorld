#include "Rectangle.h"

Rectangle::Rectangle(GameSystem *owner, Particle* particle, float ang, Vector2f size) {
	this->owner = owner;
	this->particle = particle;
	this->ang = ang;
	this->size = size;
	sprite = Sprite("data/wall.jpg");
}

void Rectangle::Update(float dt)
{ }

void Rectangle::Draw() {
	sprite.Draw(owner->GetWindow(), particle, this->ang, this->size);
}