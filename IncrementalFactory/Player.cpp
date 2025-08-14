#include "Player.h"
#include "GameObject.h"

void Player::update() {
	raycast();
	handleInputs();
}

void Player::raycast() {
	Transform* transform = getOwner()->getComponent<Transform>();

	if (transform->rotation.x <= 0 || transform->position.y <= 0) {
		return;
	}

	glm::vec3 playerDirection = transform->getForward();
	glm::vec3 gridDirection = glm::normalize(glm::vec3(sin(transform->rotation.y), 0, cos(transform->rotation.y)));

	glm::vec3 playerPosition = transform->position;
	glm::vec3 gridPlayerPosition = glm::vec3(transform->position.x, 0, transform->position.z);

	float a = glm::length(glm::cross((playerPosition - gridPlayerPosition), gridDirection)) /
		glm::length(glm::cross(playerDirection, gridDirection));

	glm::vec3 intersectionPoint = playerPosition + a * playerDirection;

	if (intersectionPoint.x < 32 && intersectionPoint.x > 0) {
		_currentTarget.x = (int)intersectionPoint.x;
	}
	if (intersectionPoint.z < 32 && intersectionPoint.z > 0) {
		_currentTarget.z = (int)intersectionPoint.z;
	}
}

void Player::handleInputs() {
	if (Input::getLeftMouseDown()) {
		std::cout << "Left Mouse";
	}
	if (Input::getRightMouseDown()) {
		std::cout << "Right Mouse";
	}
	if (_building) {
		
	}
}
