#pragma once
#include "CameraMatrix.h"
#include "glut.h"
#include <iostream>

static class Camera {
private:
	static CameraMatrix _currentCameraMatrix;
public:
	static void updateCameraMatrix(CameraMatrix cameraMatrix);
	static void applyCameraMatrix();
};

