#include "Machine.h"
#include "GameObject.h"
#include "WorldGrid.h"

Machine::Machine(float delay, std::vector<glm::vec2> inputDirections, std::vector<glm::vec2> outputDirections, std::vector<CraftingRecipe> craftingRecipes) {
    _delay = delay;
    _inputDirections = inputDirections;
    _outputPositions = outputDirections;
    _craftingRecipes = craftingRecipes;
}

Component* Machine::copy() {
    return new Machine(_delay, _inputDirections, _outputPositions, _craftingRecipes);
}
