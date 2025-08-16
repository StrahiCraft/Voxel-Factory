#pragma once
#include "Component.h"
#include "Camera.h"
#include "Input.h"

static class CameraController : public Component
{
private:
	float _flySpeed = 10;
public:
	void update();
private:
	void moveCamera();
	void rotateCamera();
	void setCameraMatrix();

	Component* copy();
};

