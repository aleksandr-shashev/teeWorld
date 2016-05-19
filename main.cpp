//#include <iostream>
#include "SFML\Graphics.hpp"
#include "GameSystem.h"
#include <iostream>

#include "Hero.h"
#include "Rectangle.h"	
#include "Spike.h"
#include "Bomb.h"
#include "Cloud.h"
#include "Background.h"




int main()
{
	auto gameSize = Vector2f(2250.0f, 1500.0f);
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Let's play!");

	GameSystem sys(&window, gameSize);

	Background* newFon = new Background(&sys, "data/fon.png", 1.0f);
	sys.AddObject(newFon);

	Cloud* oblako = new Cloud(&sys, Vector2f(2400.0f, 300.0f), 0.0f, Vector2f(600.0f, 400.0f), "data/oblako1.png", 40.0f);
	sys.AddObject(oblako);
	oblako = new Cloud(&sys, Vector2f(1400.0f, 450.0f), 0.0f, Vector2f(600.0f, 400.0f), "data/oblako2.png", 20.0f);
	sys.AddObject(oblako);
	oblako = new Cloud(&sys, Vector2f(700.0f, 200.0f), 0.0f, Vector2f(600.0f, 400.0f), "data/oblako3.png", 30.0f);
	sys.AddObject(oblako);


	Rectangle* first = new Rectangle(&sys, Vector2f(1125.0f, 1475.0f), 0.0f, Vector2f(2250.0f, 50.0f), "data/wall.jpg", 2.0f);
	sys.AddObject(first);
	first = new Rectangle(&sys, Vector2f(1500.0f, 1300.0f), 0.0f, Vector2f(1500.0f, 50.0f), "data/wall.jpg", 2.0f);
	sys.AddObject(first);
	first = new Rectangle(&sys, Vector2f(25.0f, 500.0f), 0.0f, Vector2f(50.0f, 500.0f), "data/wall.jpg", 2.0f);
	sys.AddObject(first);
	first = new Rectangle(&sys, Vector2f(800.0f, 200.0f), 0.0f, Vector2f(200.0f, 50.0f), "data/wall.jpg", 2.0f);
	sys.AddObject(first);
	first = new Rectangle(&sys, Vector2f(500.0f, 400.0f), -0.4f, Vector2f(200.0f, 50.0f), "data/wall.jpg", 2.0f);
	sys.AddObject(first);

	Spike* spike = new Spike(&sys, Vector2f(100.0f, 1400.0f), 0.0f, Vector2f(50.0f, 50.0f));
	sys.AddObject(spike);

	Hero* second = new Hero(&sys, Vector2f(600.0f, 600.0f), 10);
	sys.AddObject(second);

	float prevTime = 0;
	sf::Clock clock;
	float prevPress = clock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		float currTime = clock.getElapsedTime().asSeconds();
		float dt = currTime - prevTime;
		prevTime = currTime;

		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && currTime - prevPress > 0.3f) {

			Vector2f mousePos = Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			float pi = 3.1415926f;
			Vector2f xVector = Vector2f(-sys.cam.ang);
			Vector2f yVector = Vector2f(-sys.cam.ang + pi / 2.0f);
			Vector2f delta = mousePos - Vector2f(window.getSize().x, window.getSize().y) * 0.5f;
			delta = delta * sys.cam.fieldOfView * (1 / (float)window.getSize().x);
			mousePos = sys.cam.pos + xVector * (xVector * delta) + yVector * (yVector * delta);

			Vector2f pos = (sys.GetObject<Hero>(0))->GetCenter()->pos;
			Vector2f speed = Vector2f(mousePos.x - pos.x, mousePos.y - pos.y);
			if (speed.Length() >500.0f)
				speed = speed.GetNorm() * 500.0f;
			pos = pos + speed.GetNorm() * (sys.GetObject<Hero>(0))->GetCenter()->radius * 3.0f;
			Bomb* third = new Bomb(&sys, pos, 5, speed * 0.03f, 20.0f);
			sys.AddObject(third);

			prevPress = currTime;
		}

		float pi = 3.1415926f;
		Vector2f temp = Vector2f(sys.cam.ang);
		Vector2f temp2 = Vector2f(sys.cam.ang + pi / 2.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (sys.cam.pos.x < gameSize.x - sys.cam.fieldOfView * 0.5f)
				sys.cam.pos = sys.cam.pos + Vector2f(temp.x, temp.y)*2.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (sys.cam.pos.x > sys.cam.fieldOfView * 0.5f)
				sys.cam.pos = sys.cam.pos + Vector2f(temp.x, temp.y)*(-2.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (sys.cam.pos.y > sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f)
				sys.cam.pos = sys.cam.pos + Vector2f(temp2.x, temp2.y)*(-2.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (sys.cam.pos.y < gameSize.y - sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f)
				sys.cam.pos = sys.cam.pos + Vector2f(temp2.x, temp2.y)*2.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			bool q1 = sys.cam.pos.x >= gameSize.x - sys.cam.fieldOfView * 0.5f;
			bool q2 = sys.cam.pos.x <= sys.cam.fieldOfView * 0.5f;
			bool q3 = sys.cam.pos.y <= sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f;
			bool q4 = sys.cam.pos.y >= gameSize.y - sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f;
			if (!(q1 && q2) && !(q2 && q3)) {
				sys.cam.fieldOfView += 5.0f;
				if (q1)
					sys.cam.pos.x = gameSize.x - sys.cam.fieldOfView * 0.5f;
				if (q2)
					sys.cam.pos.x = sys.cam.fieldOfView * 0.5f;
				if (q3)
					sys.cam.pos.y = sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f;
				if (q4)
					sys.cam.pos.y = gameSize.y - sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			sys.cam.fieldOfView -= 5.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			sys.cam.ang -= 0.001f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
			sys.cam.ang += 0.001f;
		}

		if (sys.GetHeroAmount() != 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			Vector2f newPos = sys.GetObject<Hero>(0)->GetCenter()->pos;
			if (newPos.x > gameSize.x - sys.cam.fieldOfView * 0.5f) {
				if (sys.cam.pos.x > newPos.x)
					sys.cam.pos.x = newPos.x;
				else
					sys.cam.pos.x = gameSize.x - sys.cam.fieldOfView * 0.5f;
			}
			if (newPos.x < sys.cam.fieldOfView * 0.5f) {
				if (sys.cam.pos.x < newPos.x)
					sys.cam.pos.x = newPos.x;
				else
					sys.cam.pos.x = sys.cam.fieldOfView * 0.5f;
			}
			if (newPos.y < sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f) {
				if (sys.cam.pos.y < newPos.y)
					sys.cam.pos.y = newPos.y;
				else
					sys.cam.pos.y = sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f;
			}
			if (newPos.y > gameSize.y - sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f) {
				if (sys.cam.pos.y > newPos.y)
					sys.cam.pos.y = newPos.y;
				else
					sys.cam.pos.y = gameSize.y - sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f;
			}
			if (newPos.x < gameSize.x - sys.cam.fieldOfView * 0.5f && newPos.x > sys.cam.fieldOfView * 0.5f)
				sys.cam.pos.x = newPos.x;
			if (newPos.y > sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f &&
				newPos.y < gameSize.y - sys.cam.fieldOfView / window.getSize().x * window.getSize().y * 0.5f)
				sys.cam.pos.y = newPos.y;
		}

		sys.Update(1e-2f);
		sys.Draw();
		window.display ();
	}
	return 0;
}