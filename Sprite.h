#pragma once
#include "SFML/Graphics.hpp"
#include "Vector2f.h"
#include "Particle.h"
#include <string>
#include <map>
#include <math.h>

class Camera {
public:
	float ang;
	Vector2f pos;
	float fieldOfView;
};

class Sprite {
public:
	Sprite() {};
	Sprite(std::string filename, float texScale = 0.0f);
	void DrawScreenspace(sf::RenderWindow *wnd, std::vector<Vector2f> positions);
	void DrawWorldspace(sf::RenderWindow *wnd, std::vector<Particle*> particles, Camera cam);

	void DrawScreenspace(sf::RenderWindow *wnd, Vector2f screenPos, float screenAng, Vector2f screenSize, float texScale = 0.0f);
	void DrawWorldspace(sf::RenderWindow *wnd, Vector2f pos, float ang, Vector2f size, Camera cam, float texScale = 0.0f);
	void DrawBackground(sf::RenderWindow *wnd, Camera cam, float paralax);

private:
	sf::Texture *tex;
	static std::map<std::string, sf::Texture*>  textures; //static - общее поле для всех объектов класса
};