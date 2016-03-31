#ifndef VECTOR2F
#define VECTOR2F


#include <iostream>
#include <string>
/*#include <vector>
#include <cmath>
*/

namespace my
{
	class Vector2f
	{
	public:
		Vector2f ()
		{
			x = 0.0f;
			y = 0.0f;
		}
		Vector2f (float _x, float _y)
		{
			x = _x;
			this->y = _y;
		}
		~Vector2f ()
		{ }

		void Print ()
		{
			std::cout <<
				"x: " << x << "\n" <<
				"y: " << y << "\n";
		}
		float Length ()
		{
			return sqrt (x*x + y*y);
		}

		Vector2f GetNorm ()
		{
			return Vector2f (x / Length (), y / Length ());
		}

		float x, y;
	};

	Vector2f Add (Vector2f v0, Vector2f v1)
	{
		return Vector2f (v0.x + v1.x, v0.y + v1.y);
	}

	Vector2f operator +(Vector2f v0, Vector2f v1)
	{
		return Vector2f (v0.x + v1.x, v0.y + v1.y);
	}

	Vector2f operator - (Vector2f v0, Vector2f v1)
	{
		return Vector2f (v0.x - v1.x, v0.y - v1.y);
	}

	Vector2f operator * (Vector2f v0, float param)
	{
		return Vector2f (v0.x * param, v0.y * param);
	}

	Vector2f operator*(float param, Vector2f v1)
	{
		return Vector2f (v1.x*param, v1.y*param);
	}

	float operator ^ (Vector2f v1, Vector2f v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

}

#endif // !"VECTOR2F"