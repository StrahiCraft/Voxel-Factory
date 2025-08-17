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

    std::vector<GameObject*> _machinesToPlace;
    int _placingMachineIndex = 0;
public:
    void update();
    void init(GameObject* placingMachine);

    Component* copy();
private:
    void raycast();
    void handleInputs();

    void handleBuildingInputs();
    void handleNonBuildingInputs();

    void changePlacingMachine(int indexUpdate);
};

