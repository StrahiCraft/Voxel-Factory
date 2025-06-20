#pragma once
#include <vector>
#include "BoundingBox.h"
#include "GameObject.h"

#define MAX_RAY_DISTANCE 100

static class Raycast {
private:
	static std::vector<BoundingBox*> _boundingBoxes;

public:
	static void addBoundingBox(BoundingBox& boundingBox);
	static void addBoundingBox(std::vector<BoundingBox*> boundingBoxes);

	static bool castRay(glm::vec3 startPoint, glm::vec3 direction,
		GameObject* hitObject = NULL, float maxDistance = MAX_RAY_DISTANCE);
};

