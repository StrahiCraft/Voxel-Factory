#include "Transform.h"

inline glm::vec3 Transform::getForward() {
	return glm::vec3(-cos(rotation.x) * sin(rotation.y), -sin(rotation.x), cos(rotation.x) * cos(rotation.y));
}

void Transform::setForward(const glm::vec3& forward) {
	
}

inline glm::vec3 Transform::getRight() {
	return glm::vec3(cos(rotation.y), 0, -sin(rotation.y));
}

void Transform::setRight(const glm::vec3& right) {

}

inline glm::vec3 Transform::getUp() {
	return glm::cross(getForward(), getRight());
}

void Transform::setUp(const glm::vec3& up) {

}

void Transform::lookAt(const glm::vec3& target, const glm::vec3 up) {

}
