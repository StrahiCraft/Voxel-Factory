#include "Raycast.h"

std::vector<BoundingBox*> Raycast::_boundingBoxes;

void Raycast::addBoundingBox(BoundingBox& boundingBox) {

}

void Raycast::addBoundingBox(std::vector<BoundingBox*> boundingBoxes) {

}

bool Raycast::castRay(glm::vec3 startPoint, glm::vec3 direction, GameObject* hitObject, float maxDistance) {
	return false;
}
