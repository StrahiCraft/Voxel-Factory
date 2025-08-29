#include "Machine.h"
#include "GameObject.h"
#include "WorldGrid.h"

Machine::Machine(float delay, std::vector<Direction> inputDirections, std::vector<Direction> outputDirections,
    std::vector<CraftingRecipe> craftingRecipes, int price, int maxProductTypes, int maxProductsPerType) {
    _delay = delay;
    _inputDirections = inputDirections;
    _outputDirections = outputDirections;
    _craftingRecipes = craftingRecipes;

    _price = price;
    _maxProductTypes = maxProductTypes;
    _maxProductsPerType = maxProductsPerType;

    _output = new Product();

    if (nothingCrafter()) {
        _incrementTimer = true;
    }
}

void Machine::update() {
    if (_tryingToOutput) {
        outputNewProduct();
        return;
    }

    if (!_incrementTimer) {
        return;
    }

    _timer += Time::getDeltaTime();

    if (_timer >= _delay) {
        outputNewProduct();
        _timer = 0;
        if (nothingCrafter()) {
            return;
        }
        _incrementTimer = false;

        if (_tryingToOutput) {
            return;
        }

        GameObject* child = getOwner()->getChild(0);

        if (child != nullptr) {
            child->setActive(false);
        }
    }
}

int Machine::getPrice() {
    return _price;
}

ProductType Machine::getProductType() {
    if (_output.getType() != ProductType::NOTHING && _output.getType() != ProductType::INVALID) {
        return _output.getType();
    }
    if (_productsInside.getItemCount() == 0) {
        return ProductType::NOTHING;
    }
    return _productsInside.getKey(0);
}

bool Machine::tryToInsertProduct(glm::vec2 insertPoint, Product product) { 
    if (!productValidForCrafting(product) && !anyCrafter()) {
        return false;
    }

    if (!productFromValidDirection(insertPoint)) {
        return false;
    }

    if (!hasSpaceForProduct(product)) {
        return false;
    }

    return insertProduct(product);
}

bool Machine::insertProduct(Product product) {
    if (getRecipeOutput(ProductType::ANY) == ProductType::NOTHING || anyCrafter()) {
        _productsInside.addItem(product.getType(), 1);
        onProductEnter();
        return true;
    }

    if (_productsInside.containsKey(product.getType())) {
        if (_productsInside.getValue(product.getType()) < _maxProductsPerType) {
            _productsInside.setValue(product.getType(), _productsInside.getValue(product.getType() + 1));
            onProductEnter();
            return true;
        }
        return false;
    }

    if (_productsInside.getItemCount() < _maxProductTypes) {
        _productsInside.addItem(product.getType(), 1);
        onProductEnter();
        return true;
    }

    return false;
}

bool Machine::hasSpaceForProduct(Product product) {
    if (_output.getType() != ProductType::NOTHING && _output.getType() != ProductType::INVALID) {
        return false;
    }

    if (_productsInside.containsKey(product.getType())) {
        if (_productsInside.getValue(product.getType()) < _maxProductsPerType) {
            return true;
        }
        return false;
    }

    if (_productsInside.getItemCount() < _maxProductTypes) {
        return true;
    }

    return false;
}

float Machine::getCraftingCompletionAmount() {
    return _timer / _delay;
}

Component* Machine::copy() {
    return new Machine(_delay, _inputDirections, _outputDirections, _craftingRecipes, _price);
}

bool Machine::productValidForCrafting(Product product) {
    for (int i = 0; i < _craftingRecipes.size(); i++) {
        std::vector<ProductType> currentRecipeProductTypes = _craftingRecipes[i].getInputProductTypes();
        for (int j = 0; j < currentRecipeProductTypes.size(); j++) {
            if (currentRecipeProductTypes[j] == ProductType::ANY) {
                return true;
            }
            if (currentRecipeProductTypes[j] == ProductType::NOTHING) {
                return false;
            }
            if (_craftingRecipes[i].getInputProductTypes()[j] == product.getType()) {
                return true;
            }
        }
    }
    return false;
}

bool Machine::productFromValidDirection(glm::vec2 insertPoint) {
    Direction insertingFrom = directionFromPoint(insertPoint);

    for (auto& direction : _inputDirections) {
        if (direction == insertingFrom) {
            return true;
        }
    }
    return false;
}

Direction Machine::directionFromPoint(glm::vec2 point)
{
    Transform* transform = getOwner()->getComponent<Transform>();

    if (glm::ivec3(point.x, 0, point.y) == glm::ivec3(glm::round(transform->_position + transform->getTrueForward()))) {
        return Direction::FORWARD;
    }
    if (glm::ivec3(point.x, 0, point.y) == glm::ivec3(glm::round(transform->_position - transform->getTrueForward()))) {
        return Direction::BACK;
    }
    if (glm::ivec3(point.x, 0, point.y) == glm::ivec3(glm::round(transform->_position + transform->getTrueRight()))) {
        return Direction::RIGHT;
    }
    if (glm::ivec3(point.x, 0, point.y) == glm::ivec3(glm::round(transform->_position - transform->getTrueRight()))) {
        return Direction::LEFT;
    }
    return Direction::NOT_FOUND;
}

glm::vec3 Machine::pointFromDirection(Direction direction) {
    Transform* transform = getOwner()->getComponent<Transform>();

    switch (direction) {
    case Direction::FORWARD:
        return glm::round(transform->_position + transform->getTrueForward());
    case Direction::BACK:
        return glm::round(transform->_position - transform->getTrueForward());
    case Direction::RIGHT:
        return glm::round(transform->_position + transform->getTrueRight());
    case Direction::LEFT:
        return glm::round(transform->_position - transform->getTrueRight());
    }

    return transform->_position;
}

ProductType Machine::getRecipeOutput(ProductType input) {
    return getRecipeOutput(std::vector<ProductType> {input});
}

ProductType Machine::getRecipeOutput(std::vector<ProductType> input) {
    for (int i = 0; i < _craftingRecipes.size(); i++) {
        if (_craftingRecipes[i].getInputProductTypes() == input) {
            return _craftingRecipes[i].getOutputProductType();
        }
    }

    return ProductType::INVALID;
}

Product Machine::craft() {
    if (anyCrafter()) {
        Product output = Prefabs::getProduct(_productsInside.getKey(0))->getComponent<Product>();
        _productsInside.setValue(_productsInside.getKey(0), _productsInside.getValue(_productsInside.getKey(0)) - 1);

        if (_productsInside.getValue(_productsInside.getKey(0)) <= 0) {
            _productsInside.removeItem(_productsInside.getKey(0));
        }

        return output;
    }

    if (nothingCrafter()) {
        return Prefabs::getProduct(_craftingRecipes[0].getOutputProductType())->getComponent<Product>();
    }

    for (CraftingRecipe recipe : _craftingRecipes) {
        if (canCraft(recipe)) {
            removeItemsFromRecipe(recipe);
            return Prefabs::getProduct(recipe.getOutputProductType())->getComponent<Product>();
        }
    }

    return Product();
}

bool Machine::canCraft(CraftingRecipe recipe) {
    Dictionary<ProductType, int> productsToRemove;

    for (ProductType recipePart : recipe.getInputProductTypes()) {
        if (!_productsInside.containsKey(recipePart)) {
            return false;
        }
        if (productsToRemove.containsKey(recipePart)) {
            productsToRemove.setValue(recipePart, productsToRemove.getValue(recipePart) + 1);
            if (_productsInside.getValue(recipePart) < productsToRemove.getValue(recipePart)) {
                return false;
            }
            continue;
        }

        productsToRemove.addItem(recipePart, 1);
    }
    return true;
}

void Machine::removeItemsFromRecipe(CraftingRecipe recipe) {
    for (ProductType recipePart : recipe.getInputProductTypes()) {
        _productsInside.setValue(recipePart, _productsInside.getValue(recipePart) - 1);

        if (_productsInside.getValue(recipePart) <= 0) {
            _productsInside.removeItem(recipePart);
        }
    }
}

void Machine::outputNewProduct() {
   /* if (_productsInside.getItemCount() == 0 && !nothingCrafter()) {
        _tryingToOutput = false;
        return;
    }*/

    Transform* transform = getOwner()->getComponent<Transform>();

    if (_output.getType() == ProductType::NOTHING) {
        _output = craft();
    }

    if (_output.getType() == ProductType::NOTHING || _output.getType() == ProductType::INVALID) {
        return;
    }

    _tryingToOutput = true;

    for (auto& outputDirection : _outputDirections) {
        glm::vec3 outputPosition = pointFromDirection(outputDirection);

        Machine* outputMachine = WorldGrid::getMachineAt(glm::ivec2(outputPosition.x, outputPosition.z));

        if (outputMachine == nullptr) {
            continue;
        }

        if (nothingCrafter()) {
            _output = Prefabs::getProduct(getRecipeOutput(ProductType::NOTHING))->getComponent<Product>();
        }
        if (outputMachine->tryToInsertProduct(glm::ivec2(transform->_position.x, transform->_position.z), _output)) {
            _tryingToOutput = false;
            _output = new Product();
        }
    }
}

bool Machine::anyCrafter() {
    for (int i = 0; i < _craftingRecipes.size(); i++) {
        if (_craftingRecipes[i].getInputProductTypes()[0] == ProductType::ANY) {
            return true;
        }
    }
    return false;
}

bool Machine::nothingCrafter() {
    for (int i = 0; i < _craftingRecipes.size(); i++) {
        if (_craftingRecipes[i].getInputProductTypes()[0] == ProductType::NOTHING) {
            return true;
        }
    }
    return false;
}

void Machine::onProductEnter() {
    if (getRecipeOutput(ProductType::ANY) == ProductType::NOTHING) {
        CashManager::updateMoney(Prefabs::getProduct(_productsInside.getKey(0))->getComponent<Product>()->getPrice());
        _productsInside.removeItem(_productsInside.getKey(0));
        _output = new Product();
        return;
    }

    _incrementTimer = true;

    GameObject* child = getOwner()->getChild(0);

    if (child != nullptr) {
        child->setActive(true);
    }
}
