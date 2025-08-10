#include "CameraController.h"
#include "GameObject.h"

void CameraController::update() {
	moveCamera();
	setCameraMatrix();
}

void CameraController::moveCamera() {
	Transform* transform = getOwner()->getComponent<Transform>();
	if (Input::getKey('W')) {
		transform->position += transform->getForward() * (Time::getDeltaTime() * 5);
	}
	if (Input::getKey('S')) {
		transform->position += -transform->getForward() * (Time::getDeltaTime() * 5);
	}
	if (Input::getKey('A')) {
		transform->position += transform->getRight() * (Time::getDeltaTime() * 5);
	}
	if (Input::getKey('D')) {
		transform->position += -transform->getRight() * (Time::getDeltaTime() * 5);
	}
}

void CameraController::setCameraMatrix() {
	CameraMatrix newCameraMatrix = CameraMatrix();
	newCameraMatrix.position = getOwner()->getComponent<Transform>()->position;
	newCameraMatrix.target = getOwner()->getComponent<Transform>()->getForward() + newCameraMatrix.position;
	newCameraMatrix.up = getOwner()->getComponent<Transform>()->getUp();

	Camera::updateCameraMatrix(newCameraMatrix);
}
