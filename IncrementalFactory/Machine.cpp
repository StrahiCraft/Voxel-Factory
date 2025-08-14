#include "Machine.h"
#include "GameObject.h"
#include "WorldGrid.h"

Machine::Machine(){}

Machine::Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> occupiedPoints, std::vector<glm::vec2> inputPositions, std::vector<glm::vec2> outputPositions, std::vector<CraftingRecipe> craftingRecipes) {
    _delay = delay;
    _machineCenterPosition = machineCenterPosition;
    _occupiedPoints = occupiedPoints;
    _inputPositions = inputPositions;
    _outputPositions = outputPositions;
    _craftingRecipes = craftingRecipes;
    WorldGrid::placeMachine(this);
}

Machine::Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> occupiedPoints, glm::vec2 inputPosition, glm::vec2 outputPosition, std::vector<CraftingRecipe> craftingRecipes) {
    _delay = delay;
    _machineCenterPosition = machineCenterPosition;
    _occupiedPoints = occupiedPoints;
    _inputPositions.push_back(inputPosition);
    _outputPositions.push_back(outputPosition);
    _craftingRecipes = craftingRecipes;
    WorldGrid::placeMachine(this);
}

Machine::Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> inputPositions, std::vector<glm::vec2> outputPositions, std::vector<CraftingRecipe> craftingRecipes) {
    _delay = delay;
    _machineCenterPosition = machineCenterPosition;
    _inputPositions = inputPositions;
    _outputPositions = outputPositions;
    _craftingRecipes = craftingRecipes;
    WorldGrid::placeMachine(this);
}

Machine::Machine(float delay, glm::vec2 machineCenterPosition, glm::vec2 inputPosition, glm::vec2 outputPosition, std::vector<CraftingRecipe> craftingRecipes) {
    _delay = delay;
    _machineCenterPosition = machineCenterPosition;
    _inputPositions.push_back(inputPosition);
    _outputPositions.push_back(outputPosition);
    _craftingRecipes = craftingRecipes;
    WorldGrid::placeMachine(this);
}

Machine::Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> occupiedPoints, std::vector<glm::vec2> inputPositions, std::vector<glm::vec2> outputPositions, CraftingRecipe craftingRecipe) {
    _delay = delay;
    _machineCenterPosition = machineCenterPosition;
    _occupiedPoints = occupiedPoints;
    _inputPositions = inputPositions;
    _outputPositions = outputPositions;
    _craftingRecipes.push_back(craftingRecipe);
    WorldGrid::placeMachine(this);
}

Machine::Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> occupiedPoints, glm::vec2 inputPosition, glm::vec2 outputPosition, CraftingRecipe craftingRecipe) {
    _delay = delay;
    _machineCenterPosition = machineCenterPosition;
    _occupiedPoints = occupiedPoints;
    _inputPositions.push_back(inputPosition);
    _outputPositions.push_back(outputPosition);
    _craftingRecipes.push_back(craftingRecipe);
    WorldGrid::placeMachine(this);
}

Machine::Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> inputPositions, std::vector<glm::vec2> outputPositions, CraftingRecipe craftingRecipe) {
    _delay = delay;
    _machineCenterPosition = machineCenterPosition;
    _inputPositions = inputPositions;
    _outputPositions = outputPositions;
    _craftingRecipes.push_back(craftingRecipe);
    WorldGrid::placeMachine(this);
}

Machine::Machine(float delay, glm::vec2 machineCenterPosition, glm::vec2 inputPosition, glm::vec2 outputPosition, CraftingRecipe craftingRecipe) {
    _delay = delay;
    _machineCenterPosition = machineCenterPosition;
    _inputPositions.push_back(inputPosition);
    _outputPositions.push_back(outputPosition);
    _craftingRecipes.push_back(craftingRecipe);
    WorldGrid::placeMachine(this);
}

std::vector<glm::vec2> Machine::getOccupiedPoints() {
    Transform* transform = getOwner()->getComponent<Transform>();
    glm::vec3 direction = transform->getForward();

    std::vector<glm::vec2> occupiedPoints;
    occupiedPoints.push_back(_machineCenterPosition);

    for (auto position : _occupiedPoints) {
        glm::vec2 offset = glm::vec2(position.x * direction.x, position.y * direction.z);
        occupiedPoints.push_back(_machineCenterPosition + offset);
    }

    return occupiedPoints;
}