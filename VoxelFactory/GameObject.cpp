#include "GameObject.h"

GameObject::GameObject(const std::string& name, std::vector<GameObject*> children) : _name(name) {
	addComponent<Transform>();

	if (children.size() == 0) {
		return;
	}

	for (GameObject* child : children) {
		_children.push_back(child);
		child->setParent(this);
	}
}

GameObject::GameObject(GameObject* other) {
	_name = other->_name;
	_active = other->_active;
	
	for (auto& component : other->_components) {
 		_components.push_back(component->copy());
		_components.back()->setOwner(this);
	}

	for (auto& child : other->_children) {
		_children.push_back(new GameObject(child));
		_children.back()->setParent(this);
	}
}

void GameObject::update() {
	if (!_active) return;

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
		glTranslatef(transform->_position.x, transform->_position.y, transform->_position.z);
		glm::mat4 rotation_matrix = glm::mat4(transform->_rotation);
		glMultMatrixf(glm::value_ptr(rotation_matrix));
		glScalef(transform->_scale.x, transform->_scale.y, transform->_scale.z);
	}

	for (auto& component : _components) {
		component->render();
	}

	for (auto& child : _children) {
		child->render();
	}

	glPopMatrix();
}

void GameObject::printChildren() {
	std::cout << _name << ": ";
	for (auto& child : _children) {
		std::cout << child->getName() << ", ";
		child->printChildren();
		std::cout << std::endl;
	}
}

void GameObject::addComponent(Component component) {
	_components.push_back(&component);
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

void GameObject::setIgnoreParentTransform(bool value) {
	_ignoreParentTransformations = value;
}
