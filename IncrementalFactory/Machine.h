#pragma once
#include "Component.h"
#include "CraftingRecipe.h"
#include "Product.h"

class Machine :
    public Component
{
private:
    float _delay;

    glm::vec2 _machineCenterPosition;
    std::vector<glm::vec2> _occupiedPoints;

    std::vector<glm::vec2> _inputPositions;
    std::vector<glm::vec2> _outputPositions;

    std::vector<CraftingRecipe> _craftingRecipes;
    std::vector<Product> _productInside;
public:
    Machine();

    Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> occupiedPoints,
        std::vector<glm::vec2> inputPositions, std::vector<glm::vec2> outputPositions, std::vector<CraftingRecipe> craftingRecipes);

    Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> occupiedPoints,
        glm::vec2 inputPosition, glm::vec2 outputPosition, std::vector<CraftingRecipe> craftingRecipes);

    Machine(float delay, glm::vec2 machineCenterPosition,std::vector<glm::vec2> inputPositions,
        std::vector<glm::vec2> outputPositions, std::vector<CraftingRecipe> craftingRecipes);

    Machine(float delay, glm::vec2 machineCenterPosition,glm::vec2 inputPosition, glm::vec2 outputPosition,
        std::vector<CraftingRecipe> craftingRecipes);

    Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> occupiedPoints,
        std::vector<glm::vec2> inputPositions, std::vector<glm::vec2> outputPositions, CraftingRecipe craftingRecipe);

    Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> occupiedPoints,
        glm::vec2 inputPosition, glm::vec2 outputPosition, CraftingRecipe craftingRecipe);

    Machine(float delay, glm::vec2 machineCenterPosition, std::vector<glm::vec2> inputPositions,
        std::vector<glm::vec2> outputPositions, CraftingRecipe craftingRecipe);

    Machine(float delay, glm::vec2 machineCenterPosition, glm::vec2 inputPosition, glm::vec2 outputPosition,
        CraftingRecipe craftingRecipe);

    std::vector<glm::vec2> getOccupiedPoints();
};