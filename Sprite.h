#pragma once
#include "SFML/Graphics.hpp"
#include "Vector2f.h"
#include "Particle.h"
#include <string>
#include <map>

class Sprite {
public:
	Sprite() {};
	Sprite(std::string filename);
	void Draw(sf::RenderWindow *wnd, Particle *particle, float ang, Vector2f size);
	void Draw(sf::RenderWindow *wnd, std::vector<Particle*> particles);

private:
	sf::Texture *tex;
	static std::map<std::string, sf::Texture*>  textures; //static - общее поле для всех объектов класса
};