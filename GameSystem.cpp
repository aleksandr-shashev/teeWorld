#include "GameSystem.h"

GameSystem::GameSystem (sf::RenderWindow *wnd) {
	this->wnd = wnd;
	for (int i = 0; i < END; i++) {
		objectArrays.push_back(std::vector <Object *>());
	}
}

Object* GameSystem::AddObject (Object* candidate, ObjectTypes type)
{
	objectArrays[type].push_back(candidate);
	return objectArrays[type].back();
}

void GameSystem::Update(float dt) {
	for (unsigned int type = 0; type < END; type++) 
	{
		for (unsigned int object = 0; object < objectArrays[type].size(); object++) 
		{
			objectArrays[type][object]->Update(dt);
		}
	}

	for (int rectCounter = 0; rectCounter < objectArrays [RECTANGLE].size (); rectCounter++)
	{
		for (int heroCounter = 0; heroCounter < objectArrays [HERO].size (); heroCounter++)
		{
			for (int heroParticleCounter = 0;
				heroParticleCounter < objectArrays [HERO][heroCounter]->GetParticleCount ();
				heroParticleCounter++)
			{
				//if ()
				Particle* curHeroParticle =
					objectArrays [HERO][heroCounter]->GetParticle (heroParticleCounter);

				/*std::cout << "i = " << heroParticleCounter << std::endl;
				curHeroParticle->pos.Print ();
				curHeroParticle->prevPos.Print ();
				std::cout << std::endl;*/

				for (int rectParticleCounter = 0;
					rectParticleCounter < objectArrays [RECTANGLE][rectCounter]->GetParticleCount ();
					rectParticleCounter++)
				{
					int count = objectArrays [RECTANGLE] [rectCounter]->GetParticleCount ();

					Particle* curRectParticle = 
						objectArrays [RECTANGLE][rectCounter]->GetParticle (rectParticleCounter );
					Particle* nextRectParticle = 
						objectArrays [RECTANGLE][rectCounter]->
							GetParticle ((rectParticleCounter + 1) % count);
					std::cout << double(curRectParticle->pos.x - curRectParticle->prevPos.x) << std::endl;

					float kRect = (curRectParticle->pos.y - curRectParticle->prevPos.y) /
						(curRectParticle->pos.x - curRectParticle->prevPos.x);
					if (-1e-40f < (curRectParticle->pos.x - curRectParticle->prevPos.x) &&
						(curRectParticle->pos.x - curRectParticle->prevPos.x) < 1e-40f)
						kRect = 100500;

					float kHero = (curHeroParticle->pos.y - curHeroParticle->prevPos.y) /
						(curHeroParticle->pos.x - curHeroParticle->prevPos.x);
					if (-1e-40f < (curHeroParticle->pos.x - curHeroParticle->prevPos.x) &&
						(curHeroParticle->pos.x - curHeroParticle->prevPos.x) < 1e-40f)
						kHero = 100500.0f;

					if (kRect < 1e-6f) 
						kRect = 0.0f;
					if (kHero < 1e-6f)
						kHero = 0.0f;

					//std::cout << "kRect = " << kRect << " kHero = " << kHero << std::endl;

					float bRect = curRectParticle->pos.y - kRect * curRectParticle->pos.x;
					float bHero = curHeroParticle->pos.y - kHero * curHeroParticle->pos.x;

					float commonX = (bHero - bRect) / (kRect - kHero);
					if (-1e-40f < (kRect - kHero) && (kRect - kHero) < 1e-40f)
						commonX = 100500.0f;
					float commonY = (bHero - bRect) / (kRect - kHero) * kHero + bHero;
					
					if (-1e-40f < (kRect - kHero) && (kRect - kHero) < 1e-40f)
						commonY = 100500.0f;

					Vector2f commonPoint (commonX, commonY);

					if (!(curRectParticle->pos.x <= commonPoint.x &&
						  commonPoint.x <= nextRectParticle->pos.x) &&
						(curRectParticle->pos.y <= commonPoint.y &&
						 commonPoint.y <= nextRectParticle->pos.y))
						break;
					
					commonPoint.Print ();
					std::cout << std::endl;

					curHeroParticle->prevPos = commonPoint;
					//????????????????
					Vector2f normal = Vector2f (curHeroParticle->pos - nextRectParticle->pos).GetPerp ();

					float cosa = normal.x / normal.Length ();
					float sina = normal.y / normal.Length ();
					float cos2a = cosa*cosa - sina*sina;
					float sin2a = 2 * cosa*sina;
					float cosb = curHeroParticle->pos.x / normal.Length ();
					float sinb = curHeroParticle->pos.y / normal.Length ();

					float x1 = (cosa*cosb + sina*sinb);
					float y1 = (-sinb*cosa + cosb*sina);

					float x2 = cos2a*x1 - sin2a*y1;
					float y2 = +sin2a*x1 + cos2a*y1;

					curHeroParticle->pos = Vector2f (x2, y2);

					delete curRectParticle;
					delete nextRectParticle;
				}

				//objectArrays [HERO] [heroCounter]->Update (dt);
			}
		}
	}
}

void GameSystem::Draw() {
	for (unsigned int type = 0; type < END; type++) {
		for (unsigned int object = 0; object < objectArrays[type].size(); object++) {
			objectArrays[type][object]->Draw();
		}
	}
}

Object* GameSystem::GetObject (ObjectTypes type, int pos)
{
	if (pos < objectArrays[type].size ())
		return objectArrays[type][pos];
	return NULL;
}

sf::RenderWindow *GameSystem::GetWindow() {
	return wnd;
}