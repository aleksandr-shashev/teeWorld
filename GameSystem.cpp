#pragma once

#include "GameSystem.h"


GameSystem::GameSystem (sf::RenderWindow *wnd) {
	this->wnd = wnd;
}


void GameSystem::Update(float dt) 
{
	for (unsigned int object = 0; object < objectsArray.size(); object++) 
	{
		objectsArray[object]->Update(dt);
	}

	for (int i = 0; i < objectsArray.size ();)
	{
		if (!objectsArray [i]->Exist ())
		{
			objectsArray [i] = objectsArray.back ();
			objectsArray.pop_back ();
		}
		else
			i++;
	}

	GarbageCollector (heroesArray);
	GarbageCollector (rectanglesArray);


	float step = 0.01f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		(heroesArray[0])->Push(Vector2f(step, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		(heroesArray[0])->Push(Vector2f(-step, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (CanJump(0)) {
			(heroesArray[0])->Push(Vector2f(0.0f, -0.5f));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		(heroesArray[0])->Push(Vector2f(0.0f, step));
	}

	for (int rectCounter = 0; rectCounter < rectanglesArray.size(); rectCounter++)
	{
		for (int heroCounter = 0; heroCounter < heroesArray.size(); heroCounter++)
		{
			for (int heroParticleCounter = 0;
				heroParticleCounter < heroesArray [heroCounter]->GetParticleCount ();
				heroParticleCounter++)
			{
				Particle* curHeroParticle =
					heroesArray [heroCounter]->GetParticle (heroParticleCounter);
				
				if (!(rectanglesArray [rectCounter]->IsInside (curHeroParticle->pos)))
					continue;
				curHeroParticle->prevPos = curHeroParticle->pos;
				curHeroParticle->pos = curHeroParticle->pos +
						rectanglesArray [rectCounter]->GetMinPerp (curHeroParticle);
				if (rectCounter != 0)
					rectanglesArray [rectCounter]->Kill ();
			}
		}
	}
}

void GameSystem::Draw() {
	for (unsigned int object = 0; object < objectsArray.size(); object++) {
			objectsArray[object]->Draw();
	}
}


sf::RenderWindow *GameSystem::GetWindow() {
	return wnd;
}

bool GameSystem::CanJump(int hero) 
{
	for (int rectCounter = 0; rectCounter < rectanglesArray.size(); rectCounter++)
	{
		for (int j = 0; j < heroesArray [hero]->GetParticleCount(); j++) 
		{
			for (int i = 0; i < rectanglesArray [rectCounter]->GetParticleCount(); i++) 
			{
				Particle* heroParticle = heroesArray [hero]->GetParticle (j);
				Vector2f delta = rectanglesArray [rectCounter]->GetMinPerp (heroParticle);

				Particle* curRectParticle = 
					rectanglesArray [rectCounter]->GetParticle (i);
				size_t rectParticleCout = rectanglesArray [rectCounter]->GetParticleCount ();
				Particle* nextRectParticle = 
					rectanglesArray [rectCounter]->GetParticle ((i + 1) % rectParticleCout);

				if ((-1e-2f < delta.Length () && delta.Length () < 1e-2f) &&
					(curRectParticle->pos.Length () <= heroParticle->pos.Length () &&
					 heroParticle->pos.Length () <= nextRectParticle->pos.Length ()))
					return true;
			}
		}
	}
	return false;
}

