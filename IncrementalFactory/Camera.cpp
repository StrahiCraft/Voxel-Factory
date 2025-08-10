#include "Camera.h"

CameraMatrix Camera::_currentCameraMatrix;

void Camera::updateCameraMatrix(CameraMatrix cameraMatrix) {
	_currentCameraMatrix = cameraMatrix;
}

void Camera::applyCameraMatrix() {
	gluLookAt(
		_currentCameraMatrix.position.x, _currentCameraMatrix.position.y, _currentCameraMatrix.position.z,
		_currentCameraMatrix.target.x, _currentCameraMatrix.target.y, _currentCameraMatrix.target.z,
		_currentCameraMatrix.up.x, _currentCameraMatrix.up.y, _currentCameraMatrix.up.z
	);
}
