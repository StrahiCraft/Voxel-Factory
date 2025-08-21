#include "Player.h"
#include "GameObject.h"

void Player::update() {
	raycast();
	handleInputs();
}

void Player::setupMachines(GameObject* placingMachine) {
	_placingMachine = placingMachine;
	_placingMachine->setActive(false);

	_machinesToPlace.push_back(new GameObject(Prefabs::getPrefab("Conveyor")));
	_machinesToPlace.push_back(new GameObject(Prefabs::getPrefab("Wood generator")));
	_machinesToPlace.push_back(new GameObject(Prefabs::getPrefab("Stone generator")));
	_machinesToPlace.push_back(new GameObject(Prefabs::getPrefab("Iron generator")));
	_machinesToPlace.push_back(new GameObject(Prefabs::getPrefab("Saw")));
	_machinesToPlace.push_back(new GameObject(Prefabs::getPrefab("Furnace")));
	_machinesToPlace.push_back(new GameObject(Prefabs::getPrefab("Metal press")));
	_machinesToPlace.push_back(new GameObject(Prefabs::getPrefab("Seller")));
}

void Player::setupMachinePlacementText(TextRenderer* machinePlacementText) {
	_machinePlacementText = machinePlacementText;
	_machinePlacementText->getOwner()->setActive(false);
	changePlacingMachine(0);
}

void Player::setupHints(UIObject* buildHint, UIObject* rotationHint, UIObject* placeHint, UIObject* destroyHint, UIObject* scrollHint) {
	_buildHint = buildHint;
	_rotationHint = rotationHint;
	_placeHint = placeHint;
	_destroyHint = destroyHint;
	_scrollHint = scrollHint;
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
	intersectionPoint += glm::vec3(0.5f);

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

	handleMachineChange();
	handleBuildColor();

	if (Input::getLeftMouseDown()) {
		placeMachine();
	}

	if (Input::getKeyDown('B')) {
		_buildHint->getComponent<TextRenderer>()->setTextColor(glm::vec3(0, 1, 0));
		_placeHint->setActive(false);
		_scrollHint->setActive(false);

		_building = false;
		_placingMachine->setActive(false);
		_machinePlacementText->getOwner()->setActive(false);
		return;
	}

	if (Input::getKeyDown('R')) {
		AudioManager::playSound("Rotate");
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
		_buildHint->getComponent<TextRenderer>()->setTextColor(glm::vec3(1, 0, 0));
		_rotationHint->setActive(true);
		_scrollHint->setActive(true);
		_placeHint->setActive(true);
		_destroyHint->setActive(false);

		_building = true;
		_placingMachine->setActive(true);
		_machinePlacementText->getOwner()->setActive(true);
		if (targetedMachine != nullptr) {
			targetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelected(false);
		}
		if (_previousTargetedMachine != nullptr) {
			_previousTargetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelected(false);
		}
		return;
	}

	if (targetedMachine == nullptr) {
		_rotationHint->setActive(false);
		_destroyHint->setActive(false);
		return;
	}

	_rotationHint->setActive(true);
	_destroyHint->setActive(true);

	targetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelected(true);
	targetedMachine->getOwner()->getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(255.0 / 255.0, 249 / 255.0, 74 / 255.0));

	if (Input::getRightMouseDown()) {
		AudioManager::playSound("Destroy");
		WorldGrid::removeMachine(WorldGrid::getMachineAt(glm::vec2(_currentTarget.x, _currentTarget.z)));
		CashManager::updateMoney(targetedMachine->getPrice());
	}

	if (Input::getKeyDown('R')) {
		AudioManager::playSound("Rotate");
		targetedMachine->getOwner()->getComponent<Transform>()->rotate(-90, glm::vec3(0, 1, 0));
	}
}

void Player::handleMachineChange() {
	if (Input::getKeyDown('Z')) {
		changePlacingMachine(-1);
		AudioManager::playSound("ChangeMachine");
	}
	if (Input::getKeyDown('C')) {
		changePlacingMachine(1);
		AudioManager::playSound("ChangeMachine");
	}
}

void Player::handleBuildColor() {
	if (WorldGrid::isGridFreeAt(_currentTarget.x, _currentTarget.z)) {
		_placingMachine->getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(0, 1, 0));
		_placeHint->getComponent<TextRenderer>()->setTextColor(glm::vec3(0, 1, 0));
	}
	else {
		_placingMachine->getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(1, 0, 0));
		_placeHint->getComponent<TextRenderer>()->setTextColor(glm::vec3(1, 0, 0));
		return;
	}
	if (_machinesToPlace[_placingMachineIndex]->getComponent<Machine>()->getPrice() > CashManager::getCurrentCash()) {
		_placingMachine->getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(242.0 / 255.0, 89.0 / 255.0, 0));
		_placeHint->getComponent<TextRenderer>()->setTextColor(glm::vec3(242.0 / 255.0, 89.0 / 255.0, 0));
	}
}

void Player::placeMachine() {
	if (_machinesToPlace[_placingMachineIndex]->getComponent<Machine>()->getPrice() > CashManager::getCurrentCash()) {
		AudioManager::playSound("InvalidPlacement");
		return;
	}

	if (!WorldGrid::isGridFreeAt(_currentTarget.x, _currentTarget.z)) {
		AudioManager::playSound("InvalidPlacement");
		return;
	}

	GameObject* newMachine = new GameObject(_machinesToPlace[_placingMachineIndex]);
	newMachine->getComponent<Transform>()->_position = _currentTarget;
	newMachine->getComponent<Transform>()->_rotation = _placingMachine->getComponent<Transform>()->_rotation;

	WorldGrid::placeMachine(newMachine);
	WorldGrid::debugPrint();

	CashManager::updateMoney(-_machinesToPlace[_placingMachineIndex]->getComponent<Machine>()->getPrice());

	AudioManager::playSound("Place");
}

void Player::changePlacingMachine(int indexUpdate) {
	_placingMachineIndex += indexUpdate;

	if (_placingMachineIndex < 0) {
		_placingMachineIndex = _machinesToPlace.size() - 1;
	}
	
	_placingMachineIndex %= _machinesToPlace.size();

	_placingMachine->getComponent<MeshRenderer>()->setMesh(_machinesToPlace[_placingMachineIndex]->getComponent<MeshRenderer>()->getMeshes());
	std::string placementText = _machinesToPlace[_placingMachineIndex]->getName() + "\nPrice: ";
	placementText.append(std::to_string(_machinesToPlace[_placingMachineIndex]->getComponent<Machine>()->getPrice()) + "$");
	_machinePlacementText->setText(placementText);
}

Component* Player::copy() {
	return new Player();
}