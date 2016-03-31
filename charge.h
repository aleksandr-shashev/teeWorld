#include "SFML\Graphics.hpp" 
#include <cmath>
#include <vector>
#include <random>

struct Charge
{
	Charge (sf::Vector2f pos, float value) :
		_pos (pos),
		_value (value),
		_radius (20.0f)
	{
	}

	float _value;
	sf::Vector2f _pos;
	float _radius;

	float getLen (sf::Vector2f pos)
	{
		return sqrt (pow (pos.x, 2) + pow (pos.y, 2));
	}

	bool isHit (sf::Vector2f pos)
	{
		if (getLen (pos - _pos) < _radius)
			return true;
		return false;
	}
};

class ChargeSystem
{
	int _pointCount;
	float _maxLen;
	sf::Vector2f _wnd;


public:
	std::vector<Charge> chargeArray;

	ChargeSystem (int count, sf::Vector2f wnd, int pointCount = 100, float maxLen = 50.0f)
	{
		for (int i = 0; i < count; i++)
		{
			sf::Vector2f chargePos (std::rand () % (int)wnd.x, std::rand () % (int)wnd.y);
			//sf::Vector2f chargePos (1000.0f, 800.0f);
			chargeArray.push_back (Charge (chargePos, 50.0f/*std::rand () % 20 - 20.0f*/));
		}
		_wnd = wnd;
		_maxLen = maxLen;
		_pointCount = pointCount;
	}

	float getLen (sf::Vector2f pos)
	{
		return sqrt (pow (pos.x, 2) + pow (pos.y, 2));
	}

	sf::Vector2f CalcTension (sf::Vector2f pos)
	{
		sf::Vector2f sumTension (0.0, 0.0);
		float scale = 500000.0f;

		for (int i = 0; i < chargeArray.size (); i++)
		{
			sf::Vector2f delta = (pos - chargeArray [i]._pos);
			sumTension += chargeArray [i]._value*scale *
					delta / pow(getLen (delta), 3);
				
		}

		if (getLen (sumTension) > _maxLen)
			sumTension /= getLen (sumTension) / 20.0f;
		return sumTension;
	}

	sf::Vector2f getPoint (int numCharge, int numPoint)
	{
		float pi = 3.1415926f;
		float ang = float (numPoint) / _pointCount * (2.0f * pi);
		return sf::Vector2f (cosf (ang), sinf (ang)) * (chargeArray[numCharge]._radius + 5.0f) + chargeArray [numCharge]._pos;
	}

	bool checkPos (sf::Vector2f pos)
	{
		if (pos.x > _wnd.x || pos.y > _wnd.y || pos.x < 0 || pos.y < 0)
			return false;
		for (int i = 0; i < chargeArray.size (); i++)
			if (chargeArray [i].isHit (pos))
				return false;
		return true;
	}

	void drawTension (sf::RenderWindow& window)
	{
		sf::Vertex vertices [2];
		for (int i = 0; i < 2; i++)
		{
			vertices [i].color = sf::Color::Green;
		}

		for (int i = 0; i < chargeArray.size (); i++)
		{
			for (int n = 0; n < _pointCount; n++)
			{
				sf::Vector2f pos = getPoint (i, n);

				for (;;)
				{
					if (!checkPos (pos)) 
						break;

					sf::Vector2f tension (CalcTension (pos));

					vertices [0].position = sf::Vector2f (pos.x, pos.y);
					pos += tension;
					vertices [1].position = pos;

					window.draw (vertices, 2, sf::Lines);
				}
			}
		}
	}
};