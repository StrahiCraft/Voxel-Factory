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

    UIObject* _buildHint;
    UIObject* _rotationHint;
    UIObject* _destroyHint;
    UIObject* _placeHint;
    UIObject* _scrollHint;
public:
    void update();
    void setupMachines(GameObject* placingMachine);
    void setupMachinePlacementText(TextRenderer* machinePlacementText);
    void setupHints(UIObject* buildHint, UIObject* rotationHint, UIObject* placeHint, UIObject* destroyHint, UIObject* scrollHint);

    Component* copy();
private:
    void raycast();
    void handleInputs();

    void handleBuildingInputs();
    void handleNonBuildingInputs();

    void handleMachineChange();
    void handleBuildColor();

    void placeMachine();

    void changePlacingMachine(int indexUpdate);
};

