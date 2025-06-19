#include "GameObject.h"

GameObject::GameObject(const std::string& name, std::vector<GameObject*> children) : _name(name) {
	addComponent<Transform>();

	if (children.size() == 0) {
		return;
	}

	for (GameObject* child : children) {
		_children.push_back(child);
	}
}

void GameObject::update() {
	// rotation only for testing remove when done
	getComponent<Transform>()->rotation.y += Time::getRealTime() * 90;

	for (auto& component : _components) {
		component->update();
	}

	for (auto& child : _children) {
		child->update();
	}
}

void GameObject::render() {
	if (!_active) return;

	glPushMatrix();

	Transform* transform = getComponent<Transform>();
	if (transform != nullptr) {
		glTranslatef(transform->position.x, transform->position.y, transform->position.z);
		/*glm::mat4 rotation_matrix = glm::mat4(transform->rotation);
		glMultMatrixf(glm::value_ptr(rotation_matrix));*/
		glRotatef(transform->rotation.x, 1, 0, 0);
		glRotatef(transform->rotation.y, 0, 1, 0);
		glRotatef(transform->rotation.z, 0, 0, 1);
		glScalef(transform->scale.x, transform->scale.y, transform->scale.z);
	}

	for (auto& component : _components) {
		component->render();
	}

	for (auto& child : _children) {
		child->render();
	}

	glPopMatrix();
}

void GameObject::setActive(bool value) {
	_active = value;
}

bool GameObject::isActive() {
	return _active;
}

GameObject* GameObject::getChild(int index) {
	if (_children.size() <= index) {
		return nullptr;
	}

	return _children[index];
}

void GameObject::addChild(GameObject* child) {
	child->setParent(this);
	_children.push_back(child);
}

void GameObject::removeChild(int index) {
	_children.erase(_children.begin() + index);
}

void GameObject::removeChild(GameObject* child) {
	_children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
}

void GameObject::setParent(GameObject* parent) {
	_parent = parent;
}

GameObject* GameObject::getParent() {
	return _parent;
}

std::string GameObject::getName() {
	return _name;
}