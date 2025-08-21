#pragma once
#include <vector>
#include "UIObject.h"

class Scene {
private:
	std::vector<GameObject*> _objects;
	std::vector<UIObject*> _uiObjects;

public:
	void update();
	void render();

	void addObject(GameObject* newObject);
	void removeObject(GameObject* objectToRemove);

	void addUIObject(UIObject* newUIObject);
	void removeUIObject(UIObject* uiObjectToRemove);

private:
	void render3D();
	void render2D();
};

