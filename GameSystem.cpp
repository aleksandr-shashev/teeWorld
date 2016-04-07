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
	float step = 0.01f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		(objectArrays[HERO][0])->Push(Vector2f(step, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		(objectArrays[HERO][0])->Push(Vector2f(-step, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (CanJump(0)) {
			(objectArrays[HERO][0])->Push(Vector2f(0.0f, -0.5f));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		(objectArrays[HERO][0])->Push(Vector2f(0.0f, step));
	}

	for (int rectCounter = 0; rectCounter < objectArrays[RECTANGLE].size(); rectCounter++)
	{
		for (int heroCounter = 0; heroCounter < objectArrays[HERO].size(); heroCounter++)
		{
			//interactions between objects
			for (size_t j = 0; j < objectArrays[HERO][heroCounter]->GetParticleCount(); j++) {
				for (size_t i = 0; i < objectArrays[RECTANGLE][rectCounter]->GetParticleCount(); i++) {
						Vector2f delta = objectArrays[HERO][heroCounter]->GetParticle(j)->pos -
										 objectArrays[RECTANGLE][rectCounter]->GetParticle(i)->pos;
						float del = objectArrays[HERO][heroCounter]->GetParticle(j)->radius +
									objectArrays[RECTANGLE][rectCounter]->GetParticle(i)->radius - delta.Length();
						if (del > 0) {
							objectArrays[HERO][heroCounter]->GetParticle(j)->pos = objectArrays[HERO][heroCounter]->GetParticle(j)->pos + delta.GetNorm() * del * 0.5f;
							objectArrays[HERO][heroCounter]->GetParticle(j)->prevPos = objectArrays[HERO][heroCounter]->GetParticle(j)->pos;
						}
					}
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

bool GameSystem::CanJump(int hero) {
	for (int rectCounter = 0; rectCounter < objectArrays[RECTANGLE].size(); rectCounter++)
	{
		for (size_t j = 0; j < objectArrays[HERO][hero]->GetParticleCount(); j++) {
			for (size_t i = 0; i < objectArrays[RECTANGLE][rectCounter]->GetParticleCount(); i++) {
				Vector2f delta = objectArrays[HERO][hero]->GetParticle(j)->pos -
					objectArrays[RECTANGLE][rectCounter]->GetParticle(i)->pos;
				if (delta.Length() < 20.f) {
					return 1;
				}
			}
		}
	}
	return 0;
}