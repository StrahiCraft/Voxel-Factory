#pragma once
#include "Component.h"

#define RAD2ANGLE 57.295779513

class Transform : public Component {
public:
	glm::vec3 _position = { 0, 0, 0 };
	glm::quat _rotation = { 0, 0, 1, 0 };
	glm::vec3 _scale = { 1, 1, 1 };

	Transform();
	Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

	glm::vec3 getForward();
	glm::vec3 getRight();
	glm::vec3 getUp();

	glm::vec3 getTrueForward();
	glm::vec3 getTrueRight();
	glm::vec3 getTrueUp();

	void rotate(float angle, const glm::vec3& rotationAxis);

	Component* copy();
};

