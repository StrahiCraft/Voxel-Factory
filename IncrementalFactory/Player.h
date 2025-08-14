#pragma once
#include "Component.h"
#include "Input.h"
class Player :
    public Component
{
private:
    glm::vec3 _currentTarget;
    bool _building = false;
public:
    void update();
private:
    void raycast();
    void handleInputs();
};

