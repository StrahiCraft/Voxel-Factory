#pragma once
#include "Input.h"
#include "Machine.h"
#include "WorldGrid.h"
#include "Prefabs.h"

class Player :
    public Component
{
private:
    glm::vec3 _currentTarget;
    bool _building = false;

    GameObject* _placingMachine;
    Machine* _previousTargetedMachine = nullptr;
public:
    Player();

    void update();
    void setPlacingMachine();

    Component copy();
private:
    void raycast();
    void handleInputs();
};

