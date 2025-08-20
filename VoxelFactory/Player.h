#pragma once
#include "Input.h"
#include "Machine.h"
#include "WorldGrid.h"
#include "Prefabs.h"
#include "AudioManager.h"
#include "CashManager.h"

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

    TextRenderer* _machinePlacementText;
public:
    void update();
    void setupMachines(GameObject* placingMachine);
    void setupMachinePlacementText(TextRenderer* machinePlacementText);

    Component* copy();
private:
    void raycast();
    void handleInputs();

    void handleBuildingInputs();
    void handleNonBuildingInputs();

    void changePlacingMachine(int indexUpdate);
};

