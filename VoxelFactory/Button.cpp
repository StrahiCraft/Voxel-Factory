#include "Button.h"
#include "UIObject.h"

Button::Button(glm::vec2 bounds, glm::vec3 color) {
	_bounds = bounds;
	_color = color;
}

void Button::update() {
	if (!Input::getLeftMouse()) {
		return;
	}

	if (mouseInBounds()) {
		onButtonClicked();
	}
}

void Button::render() {
	glPushMatrix();

	glColor3f(_color.r, _color.g, _color.b);
	glScalef(_bounds.x, _bounds.y, 1);

	glBegin(GL_QUADS);

	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.5f, -0.5f);

	glEnd();

	glColor3f(1, 1, 1);

	glPopMatrix();
}

void Button::onButtonClicked() {
	std::cout << "Button clicked!" << std::endl;
}

Component* Button::copy() {
	return new Button(_bounds, _color);
}

bool Button::mouseInBounds() {
	glm::vec3 mousePosition = Input::getMousePosition();

	glm::vec3 boundOffset = getOwner()->getComponent<Transform>()->_position + ((UIObject*)getOwner())->getAlignmentOffset();

	return (mousePosition.x > boundOffset.x - _bounds.x / 2) && (mousePosition.x < boundOffset.x + _bounds.x / 2) &&
		(mousePosition.y > boundOffset.y - _bounds.y / 2) && (mousePosition.y < boundOffset.y + _bounds.y / 2);
}
