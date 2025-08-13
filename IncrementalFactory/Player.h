#pragma once
#include "Component.h"
#include "Input.h"
class Player :
    public Component
{
public:
    glm::vec3 _currentTarget;
public:
    void update();
private:
    void raycast();
};

