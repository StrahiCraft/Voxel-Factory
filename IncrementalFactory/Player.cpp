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

	if (transform->_rotation.x <= 0 || transform->_position.y <= 0) {
		return;
	}

	glm::vec3 playerDirection = transform->getForward();
	glm::vec3 gridDirection = glm::normalize(glm::vec3(sin(transform->_rotation.y), 0, cos(transform->_rotation.y)));

	glm::vec3 playerPosition = transform->_position;
	glm::vec3 gridPlayerPosition = glm::vec3(transform->_position.x, 0, transform->_position.z);

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
	placingMachineTransform->_position = _currentTarget;

	if (WorldGrid::isGridFreeAt(_currentTarget.x, _currentTarget.z)) {
		_placingMachine->getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(0, 1, 0));
	}
	else {
		_placingMachine->getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(1, 0, 0));
	}

	if (Input::getLeftMouseDown()) {
		// check if player has enough money
		// place machine

		if (!WorldGrid::isGridFreeAt(_currentTarget.x, _currentTarget.z)) {
			// play a cant place sound
			return;
		}

		GameObject* newMachine = new GameObject(Prefabs::getPrefab("Conveyor"));
		newMachine->getComponent<Transform>()->_position = _currentTarget;
		newMachine->getComponent<Transform>()->_rotation = _placingMachine->getComponent<Transform>()->_rotation;

		WorldGrid::placeMachine(newMachine);
	}

	if (Input::getKeyDown('B')) {
		_building = false;
		_placingMachine->setActive(false);
		return;
	}

	if (Input::getKeyDown('R')) {
		_placingMachine->getComponent<Transform>()->rotate(-90, glm::vec3(0, 1, 0));
	}

	_placingMachine->getComponent<Transform>()->_position = glm::vec3(_currentTarget.x, 0, _currentTarget.z);
}

void Player::handleNonBuildingInputs() {

	Machine* targetedMachine = WorldGrid::getMachineAt(glm::vec2(_currentTarget.x, _currentTarget.z));

	if (_previousTargetedMachine != targetedMachine) {
		if (_previousTargetedMachine != nullptr) {
			_previousTargetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelected(false);
		}
		_previousTargetedMachine = targetedMachine;
	}

	if (Input::getKeyDown('B')) {
		_building = true;
		_placingMachine->setActive(true);
		if (targetedMachine != nullptr) {
			targetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelected(false);
		}
		if (_previousTargetedMachine != nullptr) {
			_previousTargetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelected(false);
		}
	}

	if (targetedMachine == nullptr) {
		return;
	}

	targetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelected(true);
	targetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(255.0 / 255.0, 249 / 255.0, 74 / 255.0));

	if (Input::getRightMouseDown()) {
		WorldGrid::removeMachine(WorldGrid::getMachineAt(glm::vec2(_currentTarget.x, _currentTarget.z)));
	}

	if (Input::getKeyDown('R')) {
		targetedMachine->getOwner()->getComponent<Transform>()->rotate(-90, glm::vec3(0, 1, 0));
	}

}

Component* Player::copy() {
	return new Player();
}