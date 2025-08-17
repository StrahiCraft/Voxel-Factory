#include "Machine.h"
#include "GameObject.h"
#include "WorldGrid.h"

Machine::Machine(float delay, std::vector<glm::vec2> inputDirections, std::vector<glm::vec2> outputDirections,
    std::vector<CraftingRecipe> craftingRecipes, int price) {
    _delay = delay;
    _inputDirections = inputDirections;
    _outputPositions = outputDirections;
    _craftingRecipes = craftingRecipes;
    _price = price;
}

int Machine::getPrice() {
    return _price;
}


Component* Machine::copy() {
    return new Machine(_delay, _inputDirections, _outputPositions, _craftingRecipes, _price);
}
