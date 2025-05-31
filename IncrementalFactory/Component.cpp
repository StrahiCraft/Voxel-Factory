#include "Component.h"

void Component::update(float deltaTime) {}
void Component::render() {}

void Component::setOwner(GameObject* owner) {
	_owner = owner;
}

GameObject* Component::getOwner() {
	return _owner;
}
