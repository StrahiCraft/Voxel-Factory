#pragma once
#include "Component.h"
#include "Camera.h"
#include "Input.h"

static class CameraController : public Component
{
public:
	void update();
private:
	void moveCamera();
	void setCameraMatrix();
};

