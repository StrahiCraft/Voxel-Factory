#pragma once

class GameObject;

#include "glm.hpp"
#include <gtc/type_ptr.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/matrix_transform.hpp>
#include <glut.h>
#include "Time.h"
#include <iostream>

class Component {
private:
	GameObject* _owner = nullptr;
public:
	virtual ~Component() = default;
	virtual void update();
	virtual void render();

	void setOwner(GameObject* owner);
	GameObject* getOwner();
};