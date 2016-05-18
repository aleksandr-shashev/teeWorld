#include "Background.h"

Background::Background(GameSystem *owner, std::string nameOfFile, float paralax) {
	this->owner = owner;
	sprite = Sprite(nameOfFile);
	this->paralax = paralax;
}

void Background::Draw() {
	sprite.DrawBackground(owner->GetWindow(), owner->cam, paralax);
}