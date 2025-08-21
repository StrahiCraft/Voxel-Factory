#include "UIObject.h"

UIObject::UIObject(const std::string& name, ScreenAlignment screenAlignment, std::vector<UIObject*> children) {
	_name = name;
	_screenAlignment = screenAlignment;

	for (UIObject* child : children) {
		_children.push_back(child);
		child->setParent(this);
	}
}

UIObject::UIObject(UIObject* other) {
	_name = other->_name;
	_screenAlignment = other->_screenAlignment;
	_active = other->_active;

	for (auto& component : other->_components) {
		_components.push_back(component->copy());
		_components.back()->setOwner(this);
	}

	for (auto& child : other->_children) {
		_children.push_back(new UIObject((UIObject*)child));
		_children.back()->setParent(this);
	}
}

void UIObject::render() {
	if (!_active) return;

	glPushMatrix();

	align();

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

void UIObject::align() {
	glm::vec2 windowSize = Window::getWindowSize();
	switch (_screenAlignment) {
	case ScreenAlignment::BOTTOM_LEFT:
		glTranslatef(0, 0, 0);
		break;
	case ScreenAlignment::BOTTOM:
		glTranslatef(windowSize.x / 2, 0, 0);
		break;
	case ScreenAlignment::BOTTOM_RIGHT:
		glTranslatef(windowSize.x, 0, 0);
		break;
	case ScreenAlignment::CENTER_LEFT:
		glTranslatef(0, windowSize.y / 2, 0);
		break;
	case ScreenAlignment::CENTER:
		glTranslatef(windowSize.x / 2, windowSize.y / 2, 0);
		break;
	case ScreenAlignment::CENTER_RIGHT:
		glTranslatef(windowSize.x, windowSize.y / 2, 0);
		break;
	case ScreenAlignment::TOP_LEFT:
		glTranslatef(0, windowSize.y, 0);
		break;
	case ScreenAlignment::TOP:
		glTranslatef(windowSize.x / 2, windowSize.y, 0);
		break;
	case ScreenAlignment::TOP_RIGHT:
		glTranslatef(windowSize.x, windowSize.y, 0);
		break;
	}
}
