#pragma once
#include <glm.hpp>

struct BoundingBox {
	glm::vec3 maxPosition = glm::vec3(0);
	glm::vec3 minPosition = glm::vec3(0);

	bool pointInBoundingBox(glm::vec3 point) {
		return point.x < maxPosition.x &&
			point.y < maxPosition.y &&
			point.z < maxPosition.z &&
			point.x > minPosition.x &&
			point.y > minPosition.y &&
			point.z > minPosition.z;
	}
};