#include <iostream>
#include "SFML\Graphics.hpp"
#include "GameSystem.h"
#include "Hero.h"
#include "Rectangle.h"

int main ()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Let's play!");

	GameSystem sys(&window);

	Particle* particle = new Particle(Vector2f(200.0f, 200.0f));
	Rectangle* first = new Rectangle(&sys, particle, 0.0f, Vector2f(50.0f, 50.0f));
	sys.AddObject (first, RECTANGLE);
	
	Hero* second = new Hero(&sys);
	int count = 20;
	float pi = 3.1415926f;
	Vector2f circleCenter = Vector2f(500.0f, 500.0f);
	float circleRadius = 50;
	for (int i = 0; i < count; i++) {
		float ang = float(i) / count * (2.0f * pi);
		Vector2f pos = Vector2f(cosf(ang), sinf(ang)) * circleRadius + circleCenter;
		second->AddParticle(pos, 5.0f);
	}
	for (int i = 0; i < count; i++) {
		second->AddLink(second->GetParticle(i), second->GetParticle((i + 1) % count), 0.05f, 1.0f);
	}

	std::vector<Particle*> tmp;
	for (int i = 0; i < count; i++) {
		tmp.push_back(second->GetParticle(i));
	}
	second->AddVolumeLink(tmp);
	sys.AddObject(second, HERO);
	
	while (window.isOpen ())
	{
		sf::Event evt;
		while (window.pollEvent (evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				window.close ();
			}
		}
	
		window.clear ();
		sys.Update(1e-2f);
		sys.Draw();
		window.display ();
	}
	return 0;
}