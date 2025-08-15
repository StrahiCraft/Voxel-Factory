#pragma once
#include "Component.h"

#define RAD2ANGLE 57.295779513

class Transform : public Component {
public:
	glm::vec3 position = { 0, 0, 0 };
	glm::quat rotation = { 0, 0, 1, 0 };
	glm::vec3 scale = { 1, 1, 1 };

	glm::vec3 getForward();
	void setForward(const glm::vec3& forward);

	glm::vec3 getRight();
	void setRight(const glm::vec3& right);

	glm::vec3 getUp();
	void setUp(const glm::vec3& up);

	void lookAt(const glm::vec3& target);

	void rotate(float angle, const glm::vec3& rotationAxis);

	Component copy();
};

