//#include <iostream>
#include "SFML\Graphics.hpp"
#include "GameSystem.h"
#include "Hero.h"
#include "Rectangle.h"

int main ()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Let's play!");

	GameSystem sys(&window);

	Rectangle* first = new Rectangle(&sys, Vector2f(500.0f, 975.0f), 0.0f, Vector2f(1000.0f, 50.0f));
	sys.AddObject(first, RECTANGLE);
	first = new Rectangle(&sys, Vector2f(25.0f, 500.0f), 0.0f, Vector2f(50.0f, 500.0f));
	sys.AddObject(first, RECTANGLE);		
	first = new Rectangle(&sys, Vector2f(800.0f, 200.0f), 0.0f, Vector2f(200.0f, 50.0f));
	sys.AddObject(first, RECTANGLE);
	first = new Rectangle(&sys, Vector2f(500.0f, 400.0f), -0.4f, Vector2f(200.0f, 50.0f));
	sys.AddObject(first, RECTANGLE);
	
	Hero* second = new Hero(&sys);
	int count = 20;
	float pi = 3.1415926f;
	Vector2f circleCenter = Vector2f(900.0f, 900.0f);
	float circleRadius = 25;
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
	second->AddVolumeLink(tmp, 0.2f, 0.1f);
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