#pragma once
#include "Component.h"

class Transform : public Component {
public:
	glm::vec3 position = { 0, 0, 0 };
	glm::quat rotation = { 0, 0, 1, 0 };
	glm::vec3 scale = { 1, 1, 1 };
};

