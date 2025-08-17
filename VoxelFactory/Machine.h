#pragma once
#include "Component.h"
#include "CraftingRecipe.h"
#include "Product.h"

class Machine :
    public Component
{
private:
    float _delay;

    std::vector<glm::vec2> _inputDirections;
    std::vector<glm::vec2> _outputPositions;

    std::vector<CraftingRecipe> _craftingRecipes;
    std::vector<Product> _productInside;
public:
    Machine(float delay, std::vector<glm::vec2> inputPositions, std::vector<glm::vec2> outputPositions, std::vector<CraftingRecipe> craftingRecipes);

    Component* copy();
};