#include "Transform.h"

Transform::Transform() {}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale) {
	_position = position;
	_rotation = rotation;
	_scale = scale;
}

glm::vec3 Transform::getTrueForward() {
	return glm::vec3(0, 0, -1) + 2.0f * glm::cross(glm::vec3(_rotation.x, _rotation.y, _rotation.z),
		glm::cross(glm::vec3(_rotation.x, _rotation.y, _rotation.z), glm::vec3(0, 0, -1)) + _rotation.w * glm::vec3(0, 0, -1));
}

glm::vec3 Transform::getTrueRight() {
	return glm::vec3(1, 0, 0) + 2.0f * glm::cross(glm::vec3(_rotation.x, _rotation.y, _rotation.z),
		glm::cross(glm::vec3(_rotation.x, _rotation.y, _rotation.z), glm::vec3(1, 0, 0)) + _rotation.w * glm::vec3(1, 0, 0));
}

glm::vec3 Transform::getTrueUp() {
	return glm::vec3(0, 1, 0) + 2.0f * glm::cross(glm::vec3(_rotation.x, _rotation.y, _rotation.z),
		glm::cross(glm::vec3(_rotation.x, _rotation.y, _rotation.z), glm::vec3(0, 1, 0)) + _rotation.w * glm::vec3(0, 1, 0));
}

glm::vec3 Transform::getForward() {
	return glm::normalize(glm::vec3(
		cos(_rotation.x) * sin(_rotation.y),
		-sin(_rotation.x),
		cos(_rotation.x) * cos(_rotation.y)));
}

glm::vec3 Transform::getRight() {
	return glm::normalize(glm::vec3(cos(_rotation.y), 0, -sin(_rotation.y)));
}

glm::vec3 Transform::getUp() {
	return glm::normalize(glm::cross(getForward(), getRight()));
}

void Transform::rotate(float angle, const glm::vec3& rotationAxis) {
	_rotation = glm::normalize(glm::rotate(_rotation, angle / (float)RAD2ANGLE, rotationAxis));
}

Component* Transform::copy() {
	return new Transform(_position, _rotation, _scale);
}