#include "CameraController.h"
#include "GameObject.h"

void CameraController::update() {
	moveCamera();
	rotateCamera();
	setCameraMatrix();
}

//void CameraController::moveCamera() {
//	Transform* transform = getOwner()->getComponent<Transform>();
//	if (Input::getKey('W')) {
//		transform->_position += transform->getForward() * (Time::getDeltaTime() * _flySpeed);
//	}
//	if (Input::getKey('A')) {
//		transform->_position += -transform->getRight() * (Time::getDeltaTime() * _flySpeed);
//	}
//	if (Input::getKey('S')) {
//		transform->_position += -transform->getForward() * (Time::getDeltaTime() * _flySpeed);
//	}
//	if (Input::getKey('D')) {
//		transform->_position += transform->getRight() * (Time::getDeltaTime() * _flySpeed);
//	}
//	if (Input::getKey('E')) {
//		transform->_position += glm::vec3(0, 1, 0) * (Time::getDeltaTime() * _flySpeed);
//	}
//	if (Input::getKey('Q')) {
//		transform->_position += glm::vec3(0, -1, 0) * (Time::getDeltaTime() * _flySpeed);
//	}
//}
//
//void CameraController::rotateCamera() {
//	Transform* transform = getOwner()->getComponent<Transform>();
//	glm::vec3 mouseMovement = Input::getMouseDeltaPosition();
//
//	float yRotation = mouseMovement.x * Time::getDeltaTime() * 10;
//	float xRotation = mouseMovement.y * Time::getDeltaTime() * 10;
//
//	transform->rotate(xRotation, glm::vec3(1, 0, 0));
//	transform->rotate(yRotation, glm::vec3(0, 1, 0));
//
//	glm::vec3 rotation = transform->getEulerAngles();
//	rotation.z = 0;
//	rotation.x = glm::clamp<float>(rotation.x, -90, 90);
//
//	transform->setEulerAngles(rotation);
//	rotation = transform->getEulerAngles();
//
//	std::cout << glm::eulerAngles(transform->_rotation).x * RAD2ANGLE << " " << glm::eulerAngles(transform->_rotation).y * RAD2ANGLE <<
//		" " << glm::eulerAngles(transform->_rotation).z * RAD2ANGLE << std::endl;
//}


void CameraController::moveCamera() {
	Transform* transform = getOwner()->getComponent<Transform>();
	if (Input::getKey('W')) {
		transform->_position += transform->getForward() * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('A')) {
		transform->_position += transform->getRight() * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('S')) {
		transform->_position += -transform->getForward() * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('D')) {
		transform->_position += -transform->getRight() * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('E')) {
		transform->_position += glm::vec3(0, 1, 0) * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('Q')) {
		transform->_position += glm::vec3(0, -1, 0) * (Time::getDeltaTime() * _flySpeed);
	}
}

void CameraController::rotateCamera() {
	Transform* transform = getOwner()->getComponent<Transform>();
	glm::vec3 mouseMovement = Input::getMouseDeltaPosition();

	float yRotation = mouseMovement.x * Time::getDeltaTime() * 0.1f;
	float xRotation = mouseMovement.y * Time::getDeltaTime() * 0.1f;

	transform->_rotation.y += yRotation;
	transform->_rotation.x -= xRotation;
	transform->_rotation.x = glm::clamp<float>(transform->_rotation.x, -90 / RAD2ANGLE, 90 / RAD2ANGLE);
}

void CameraController::setCameraMatrix() {
	CameraMatrix newCameraMatrix = CameraMatrix();
	newCameraMatrix.position = getOwner()->getComponent<Transform>()->_position;
	newCameraMatrix.target = getOwner()->getComponent<Transform>()->getForward() + newCameraMatrix.position;
	newCameraMatrix.up = getOwner()->getComponent<Transform>()->getUp();

	Camera::updateCameraMatrix(newCameraMatrix);
}

Component* CameraController::copy() {
	return new CameraController();
}