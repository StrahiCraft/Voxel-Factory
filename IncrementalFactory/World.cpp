#include "World.h"

std::vector<GameObject*> World::_objects;

void World::update() {
	for (int i = 0; i < _objects.size(); i++) {
		_objects[i]->update();
	}
}

void World::render() {
	for (int i = 0; i < _objects.size(); i++) {
		_objects[i]->render();
	}
}

void World::addObject(GameObject* newObject) {
	_objects.push_back(newObject);
}

void World::removeObject(GameObject* objectToRemove) {
	_objects.erase(std::remove(_objects.begin(), _objects.end(), objectToRemove), _objects.end());
}

void World::listObjects() {
	for (auto& object : _objects) {
		std::cout << object->getName() << std::endl;
		object->printChildren();
		std::cout << std::endl;
	}
}
