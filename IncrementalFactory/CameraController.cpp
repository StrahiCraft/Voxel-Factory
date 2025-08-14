#include "CameraController.h"
#include "GameObject.h"

void CameraController::update() {
	moveCamera();
	rotateCamera();
	setCameraMatrix();
}

void CameraController::moveCamera() {
	Transform* transform = getOwner()->getComponent<Transform>();
	if (Input::getKey('W')) {
		transform->position += transform->getForward() * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('A')) {
		transform->position += transform->getRight() * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('S')) {
		transform->position += -transform->getForward() * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('D')) {
		transform->position += -transform->getRight() * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('E')) {
		transform->position += glm::vec3(0, 1, 0) * (Time::getDeltaTime() * _flySpeed);
	}
	if (Input::getKey('Q')) {
		transform->position += glm::vec3(0, -1, 0) * (Time::getDeltaTime() * _flySpeed);
	}
}

void CameraController::rotateCamera() {
	Transform* transform = getOwner()->getComponent<Transform>();
	glm::vec3 mouseMovement = Input::getMouseDeltaPosition();

	float yRotation = mouseMovement.x * Time::getDeltaTime() * 0.1f;
	float xRotation = mouseMovement.y * Time::getDeltaTime() * 0.1f;
	
	transform->rotation.y += yRotation;
	transform->rotation.x -= xRotation;
	transform->rotation.x = glm::clamp<float>(transform->rotation.x, -90 / RAD2ANGLE, 90 / RAD2ANGLE);
}

void CameraController::setCameraMatrix() {
	CameraMatrix newCameraMatrix = CameraMatrix();
	newCameraMatrix.position = getOwner()->getComponent<Transform>()->position;
	newCameraMatrix.target = getOwner()->getComponent<Transform>()->getForward() + newCameraMatrix.position;
	newCameraMatrix.up = getOwner()->getComponent<Transform>()->getUp();

	Camera::updateCameraMatrix(newCameraMatrix);
}

Component CameraController::copy() {
	return CameraController();
}