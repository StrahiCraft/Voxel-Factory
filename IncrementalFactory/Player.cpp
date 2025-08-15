#include "Player.h"
#include "GameObject.h"

void Player::update() {
	raycast();
	handleInputs();
}

void Player::setPlacingMachine(GameObject* placingMachine) {
	_placingMachine = placingMachine;
	_placingMachine->setActive(false);
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
	if (_building) {
		handleBuildingInputs();
		return;
	}

	handleNonBuildingInputs();
}

void Player::handleBuildingInputs() {
	Transform* placingMachineTransform = _placingMachine->getComponent<Transform>();
	placingMachineTransform->position = _currentTarget;
	if (Input::getLeftMouseDown()) {
		// check if player has enough money
		// place machine
	}

	if (Input::getKeyDown('B')) {
		_building = false;
		_placingMachine->setActive(false);
		return;
	}

	if (Input::getKeyDown('R')) {
		_placingMachine->getComponent<Transform>()->rotate(90, glm::vec3(0, 1, 0));
	}

	_placingMachine->getComponent<Transform>()->position = glm::vec3(_currentTarget.x, 0, _currentTarget.z);
}

void Player::handleNonBuildingInputs() {
	if (Input::getKeyDown('B')) {
		_building = true;
		_placingMachine->setActive(true);
		return;
	}

	Machine* targetedMachine = WorldGrid::getMachineAt(_currentTarget);

	if (_previousTargetedMachine != targetedMachine) {
		if (_previousTargetedMachine != nullptr) {
			_previousTargetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelected(false);
		}
		_previousTargetedMachine = targetedMachine;
	}

	if (targetedMachine == nullptr) {
		return;
	}

	targetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelected(true);
	targetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(255.0 / 255.0, 249 / 255.0, 74 / 255.0));

	if (Input::getRightMouseDown()) {
		// TODO destroy machine
		WorldGrid::getMachineAt(_currentTarget);
		std::cout << "Right Mouse";
	}

	if (Input::getKeyDown('R')) {
		targetedMachine->getOwner()->getComponent<Transform>()->rotation.y += 90;
	}
}

Component Player::copy() {
	return Player();
}