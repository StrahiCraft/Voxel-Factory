#include "Transform.h"

// TODO Fix setting directions
// pitch = x rot
// yaw = y rot
// roll = z rot

glm::vec3 Transform::getForward() {
	return glm::normalize(glm::vec3(
		cos(rotation.x) * sin(rotation.y),
		-sin(rotation.x),
		cos(rotation.x) * cos(rotation.y)));
}

void Transform::setForward(const glm::vec3& forward) {
	rotation.x = acos(glm::dot(forward, glm::vec3(0, 1, 0)) / 
		sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z)) * RAD2ANGLE;

	rotation.y = acos(glm::dot(forward, glm::vec3(1, 0, 0)) /
		sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z)) * RAD2ANGLE;
}

glm::vec3 Transform::getRight() {
	return glm::normalize(glm::vec3(cos(rotation.y), 0, -sin(rotation.y)));
}

void Transform::setRight(const glm::vec3& right) {
	rotation.y = acos(glm::dot(right, glm::vec3(0, 1, 0)) /
		sqrt(right.x * right.x + right.y * right.y + right.z * right.z)) * RAD2ANGLE;

	rotation.x = acos(glm::dot(right, glm::vec3(1, 0, 0)) /
		sqrt(right.x * right.x + right.y * right.y + right.z * right.z)) * RAD2ANGLE;
}

glm::vec3 Transform::getUp() {
	return glm::normalize(glm::cross(getForward(), getRight()));
}

void Transform::setUp(const glm::vec3& up) {
	rotation.z = acos(glm::dot(up, glm::vec3(0, 0, 1)) /
		sqrt(up.x * up.x + up.y * up.y + up.z * up.z)) * RAD2ANGLE;

	rotation.x = acos(glm::dot(up, glm::vec3(1, 0, 0)) /
		sqrt(up.x * up.x + up.y * up.y + up.z * up.z)) * RAD2ANGLE;
}

void Transform::lookAt(const glm::vec3& target) {
	setForward(glm::normalize(target - position));
}

void Transform::rotate(float angle, const glm::vec3& rotationAxis) {
	rotation = glm::rotate(rotation, angle / (float)RAD2ANGLE, rotationAxis);
}

Component Transform::copy() {
	return Transform();
}