#include <iostream>
#include "physics.h"
#include "SFML\Graphics.hpp"

int main ()
{
	std::cout << "Hello, World!";
	ParticleSystem sys;

	Hero* gish = new Hero (sf::Vector2f (100.0f, 100.0f));

	sys.addObject (gish, HERO);

	sf::RenderWindow window (sf::VideoMode (2000, 1700), "Awesome window");

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
		
		window.display ();
	}
	return 0;
}