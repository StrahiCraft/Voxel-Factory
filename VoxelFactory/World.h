#pragma once
#include "GameObject.h"
static class World
{
private:
	static std::vector<GameObject*> _objects;
	static std::vector<GameObject*> _uiObjects;
public:
	static void update();
	static void render();

	static void addObject(GameObject* newObject);
	static void removeObject(GameObject* objectToRemove);

	static void addUIObject(GameObject* newObject);
	static void removeUIObject(GameObject* objectToRemove);
};

