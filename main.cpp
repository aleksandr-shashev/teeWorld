//#include <iostream>
#include "SFML\Graphics.hpp"
#include "GameSystem.h"

#include "Hero.h"
#include "Rectangle.h"	
#include "Spike.h"
#include "Background.h"



int main ()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Let's play!");

	GameSystem sys(&window);

	Background* ground = new Background (&sys,
										 Vector2f (1000.0f / 2.0f, 1000.0f / 2.0f),
										 0.0f,
										 Vector2f (1000.0f, 1000.0f));
	sys.AddObject (ground);

	Rectangle* first = new Rectangle(&sys, Vector2f(500.0f, 975.0f), 0.0f, Vector2f(1000.0f, 50.0f));
	sys.AddObject (first);
	first = new Rectangle(&sys, Vector2f(25.0f, 500.0f), 0.0f, Vector2f(50.0f, 500.0f));
	sys.AddObject (first);
	first = new Rectangle(&sys, Vector2f(800.0f, 200.0f), 0.0f, Vector2f(200.0f, 50.0f));
	sys.AddObject (first);
	first = new Rectangle(&sys, Vector2f(500.0f, 400.0f), -0.4f, Vector2f(200.0f, 50.0f));
	sys.AddObject (first);
	
	Spike* spike = new Spike (&sys, Vector2f (100.0f, 925.0f), 0.0f, Vector2f (50.0f, 50.0f));
	sys.AddObject (spike);

	sys.CreateHero();
	
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