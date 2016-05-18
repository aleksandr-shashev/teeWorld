#pragma once

#include "GameSystem.h"
#include "Rectangle.h"
#include "Hero.h"
#include "Bomb.h"
#include "Spike.h"


GameSystem::GameSystem (sf::RenderWindow *wnd, Vector2f gameSize) {
	this->wnd = wnd;
	this->gameSize = gameSize;
	cam.pos.x = gameSize.x / 2.0f;
	cam.pos.y = gameSize.y / 2.0f;
	cam.fieldOfView = wnd->getSize().x;
	cam.ang = 0.0f;
}

int GameSystem::GetHeroAmount() {
	return heroesArray.size();
};

void GameSystem::Update(float dt) 
{
	
	if (heroesArray.size() == 0) {
		Hero* second = new Hero(this, Vector2f(600.0f, 600.0f), 10);
		AddObject(second);
	}

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

	GarbageCollector(bombsArray);
	GarbageCollector (heroesArray);
	GarbageCollector (rectanglesArray);

	HandleRectangles();
	HandleSpikes();

	float step = 0.1f;

	if (heroesArray.size ())
	{
		if ((heroesArray[0]->GetCenter()->pos - heroesArray[0]->GetCenter()->prevPos).Length() < 0.08f) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				(heroesArray[0])->Push(Vector2f(step, 0.0f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				(heroesArray[0])->Push(Vector2f(-step, 0.0f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (CanJump(0))
				{
					(heroesArray[0])->Push(Vector2f(0.0f, -1.5f));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				(heroesArray[0])->Push(Vector2f(0.0f, step));
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

Vector2f GameSystem::GetGameSize() {
	return gameSize;
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


void GameSystem::HandleRectangles ()
{
	for (int rectCounter = 0; rectCounter < rectanglesArray.size (); rectCounter++)
	{
		for (int heroCounter = 0; heroCounter < heroesArray.size (); heroCounter++)
		{
			Particle* curHeroCenter =
				heroesArray[heroCounter]->GetCenter();
			for (int heroParticleCounter = 0;
			heroParticleCounter < heroesArray [heroCounter]->GetParticleCount ();
				heroParticleCounter++)
			{
				Particle* curHeroParticle =
					heroesArray [heroCounter]->GetParticle (heroParticleCounter);

				if (!(rectanglesArray [rectCounter]->IsInside (curHeroParticle->pos)))
					continue;
				curHeroCenter->prevPos = curHeroCenter->pos;
				curHeroParticle->prevPos = curHeroParticle->pos;
				curHeroParticle->pos = curHeroParticle->pos +
					rectanglesArray [rectCounter]->GetMinPerp (curHeroParticle);
				//if (rectCounter != 0)
					//rectanglesArray [rectCounter]->Kill ();
			}
		}

		for (int bombCounter = 0; bombCounter < bombsArray.size(); bombCounter++)
		{
			Particle* curBombCenter =
				bombsArray[bombCounter]->GetCenter();
			for (int bombParticleCounter = 0;
			bombParticleCounter < bombsArray[bombCounter]->GetParticleCount();
				bombParticleCounter++)
			{
				Particle* curBombParticle =
					bombsArray[bombCounter]->GetParticle(bombParticleCounter);

				if (!(rectanglesArray[rectCounter]->IsInside(curBombParticle->pos)))
					continue;

				if (bombsArray[bombCounter]->GetParticleCount() > 3) {
					Vector2f speed = rectanglesArray[rectCounter]->GetMinPerp(curBombParticle);
					speed = speed.GetNorm() * 4.0f;
					Vector2f pos = bombsArray[bombCounter]->GetCenter()->pos;
					Bomb* third = new Bomb(this, pos, bombsArray[bombCounter]->GetParticleCount() - 1, speed * 1.25f, bombsArray[bombCounter]->GetRadius() * 0.7f);
					AddObject(third);
					Vector2f speed2 = speed + speed.GetPerp() * speed.Length() * 0.25f;
					third = new Bomb(this, pos, bombsArray[bombCounter]->GetParticleCount() - 1, speed2, bombsArray[bombCounter]->GetRadius() * 0.7f);
					AddObject(third);
					speed2 = speed - speed.GetPerp() * speed.Length() * 0.25f;
					third = new Bomb(this, pos, bombsArray[bombCounter]->GetParticleCount() - 1, speed2, bombsArray[bombCounter]->GetRadius() * 0.7f);
					AddObject(third);
				}
				bombsArray[bombCounter]->Kill();
				
				//if (rectCounter != 0)
					//rectanglesArray[rectCounter]->Kill();
			}
		}
	}
}
void GameSystem::HandleSpikes ()
{
	for (int spikeCounter = 0; spikeCounter < spikesArray.size(); spikeCounter++)
	{
		for (int heroCounter = 0; heroCounter < heroesArray.size(); heroCounter++)
		{
			for (int heroParticleCounter = 0;
				heroParticleCounter < heroesArray [heroCounter]->GetParticleCount ();
				heroParticleCounter++)
			{
				Particle* curHeroParticle =
					heroesArray [heroCounter]->GetParticle (heroParticleCounter);
				
				if (!(spikesArray [spikeCounter]->IsInside (curHeroParticle->pos)))
					continue;
				curHeroParticle->prevPos = curHeroParticle->pos;
				curHeroParticle->pos = curHeroParticle->pos +
						spikesArray [spikeCounter]->GetMinPerp (curHeroParticle);
				heroesArray [heroCounter]->Kill ();
				break;

			}
		}
	}
}