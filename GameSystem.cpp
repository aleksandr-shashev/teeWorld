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
	for (unsigned int type = 0; type < END; type++) {
		for (unsigned int object = 0; object < objectArrays[type].size(); object++) {
			objectArrays[type][object]->Update(dt);
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