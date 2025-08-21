#pragma once
#include <vector>
#include "GameObject.h"

class Scene {
private:
	std::vector<GameObject*> _objects;
	std::vector<GameObject*> _uiObjects;

public:
	void update();
	void render();

	void addObject(GameObject* newObject);
	void removeObject(GameObject* objectToRemove);

	void addUIObject(GameObject* newUIObject);
	void removeUIObject(GameObject* uiObjectToRemove);

private:
	void render3D();
	void render2D();
};

