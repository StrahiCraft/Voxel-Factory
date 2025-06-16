#pragma once
#include "Component.h"

class Transform : public Component {
public:
	glm::vec3 position = { 0, 0, 0 };
	glm::quat rotation = { 0, 0, 1, 0 };
	glm::vec3 scale = { 1, 1, 1 };

	inline glm::vec3 getForward();
	void setForward(const glm::vec3& forward);

	inline glm::vec3 getRight();
	void setRight(const glm::vec3& right);

	inline glm::vec3 getUp();
	void setUp(const glm::vec3& up);

	void lookAt(const glm::vec3& target, const glm::vec3 up = glm::vec3(0, 0, 1));
};

