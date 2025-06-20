#include "BoundingBox.h"

void BoundingBox::setBounds(glm::vec3 maxPosition, glm::vec3 minPosition) {
	_maxPosition = maxPosition;
	_minPosition = minPosition;
}

bool BoundingBox::pointInBoundingBox(glm::vec3 point) {
	return point.x < _maxPosition.x &&
		point.y < _maxPosition.y &&
		point.z < _maxPosition.z &&
		point.x > _minPosition.x &&
		point.y > _minPosition.y &&
		point.z > _minPosition.z;
}

void BoundingBox::setNewMaxPosition(glm::vec3 position) {
	if (position.x > _maxPosition.x) {
		_maxPosition.x = position.x;
	}
	if (position.y > _maxPosition.y) {
		_maxPosition.y = position.y;
	}
	if (position.z > _maxPosition.z) {
		_maxPosition.z = position.z;
	}
}

void BoundingBox::setNewMinPosition(glm::vec3 position) {
	if (position.x < _minPosition.x) {
		_minPosition.x = position.x;
	}
	if (position.y < _minPosition.y) {
		_minPosition.y = position.y;
	}
	if (position.z < _minPosition.z) {
		_minPosition.z = position.z;
	}
}
