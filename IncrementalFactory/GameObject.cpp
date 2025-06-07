#include "GameObject.h"

GameObject::GameObject(const std::string& name) : _name(name) {
	addComponent<Transform>();
}

void GameObject::update(float deltaTime)
{
	for (auto& component : _components) {
		component->update(deltaTime);
	}
}

void GameObject::render()
{
	if (!_active) return;

	glPushMatrix();

	Transform* transform = getComponent<Transform>();
	if (transform != nullptr) {
		glTranslatef(transform->position.x, transform->position.y, transform->position.z);
		glm::mat4 rotation_matrix = glm::mat4(transform->rotation);
		glMultMatrixf(glm::value_ptr(rotation_matrix));
		glScalef(transform->scale.x, transform->scale.y, transform->scale.z);
	}

	for (auto& component : _components) {
		component->render();
	}

	glPopMatrix();
}

void GameObject::setActive(bool value) {
	_active = value;
}

bool GameObject::isActive() {
	return _active;
}

std::string GameObject::getName() {
	return _name;
}