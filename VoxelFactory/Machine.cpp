#include "Machine.h"
#include "GameObject.h"
#include "WorldGrid.h"

Machine::Machine(float delay, std::vector<Direction> inputDirections, std::vector<Direction> outputDirections,
    std::vector<CraftingRecipe> craftingRecipes, int price) {
    _delay = delay;
    _inputDirections = inputDirections;
    _outputDirections = outputDirections;
    _craftingRecipes = craftingRecipes;

    _price = price;
    _productInside = new Product();

    if (nothingCrafter()) {
        _incrementTimer = true;
    }
}

void Machine::update() {
    if (!_incrementTimer) {
        return;
    }

    _timer += Time::getDeltaTime();

    if (_timer >= _delay) {
        craftNewProduct();
        _timer = 0;
        if (nothingCrafter()) {
            return;
        }
        _incrementTimer = false;

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
    return _productInside.getType();
}

void Machine::tryToInsertProduct(glm::vec2 insertPoint, Product product) { 
    if (!productValidForCrafting(product) && !anyCrafter()) {
        return;
    }

    if (!productFromValidDirection(insertPoint)) {
        return;
    }

    _productInside = product;

    onProductEnter();
}

float Machine::getCraftingCompletionAmount() {
    return _timer / _delay;
}

Component* Machine::copy() {
    return new Machine(_delay, _inputDirections, _outputDirections, _craftingRecipes, _price);
}

bool Machine::productValidForCrafting(Product product) {
    for (int i = 0; i < _craftingRecipes.size(); i++) {
        ProductType currentRecipeProductType = _craftingRecipes[i].getInputProductType();
        if (currentRecipeProductType == ProductType::ANY) {
            return true;
        }
        if (currentRecipeProductType == ProductType::NOTHING) {
            return false;
        }
        if (_craftingRecipes[i].getInputProductType() == product.getType()) {
            return true;
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

    if (glm::ivec3(point.x, 0, point.y) == glm::ivec3(transform->_position + transform->getTrueForward())) {
        return Direction::FORWARD;
    }
    if (glm::ivec3(point.x, 0, point.y) == glm::ivec3(transform->_position - transform->getTrueForward())) {
        return Direction::BACK;
    }
    if (glm::ivec3(point.x, 0, point.y) == glm::ivec3(transform->_position + transform->getTrueRight())) {
        return Direction::RIGHT;
    }
    if (glm::ivec3(point.x, 0, point.y) == glm::ivec3(transform->_position - transform->getTrueRight())) {
        return Direction::LEFT;
    }
    return Direction::NOT_FOUND;
}

glm::vec3 Machine::pointFromDirection(Direction direction) {
    Transform* transform = getOwner()->getComponent<Transform>();

    switch (direction) {
    case Direction::FORWARD:
        return transform->_position + transform->getTrueForward();
    case Direction::BACK:
        return transform->_position - transform->getTrueForward();
    case Direction::RIGHT:
        return transform->_position + transform->getTrueRight();
    case Direction::LEFT:
        return transform->_position - transform->getTrueRight();
    }

    return transform->_position;
}

ProductType Machine::getRecipeOutput(ProductType input) {
    for (int i = 0; i < _craftingRecipes.size(); i++) {
        if (_craftingRecipes[i].getInputProductType() == input) {
            return _craftingRecipes[i].getOutputProductType();
        }
    }

    return ProductType::INVALID;
}

void Machine::craftNewProduct() {
    Transform* transform = getOwner()->getComponent<Transform>();
    if (!anyCrafter() && !nothingCrafter()) {
        GameObject* product = Prefabs::getProduct(getRecipeOutput(_productInside.getType()));
        _productInside = product->getComponent<Product>();
    }

    for (auto& outputDirection : _outputDirections) {
        glm::vec3 outputPosition = pointFromDirection(outputDirection);

        Machine* outputMachine = WorldGrid::getMachineAt(glm::vec2((int)outputPosition.x, (int)outputPosition.z));

        if (outputMachine == nullptr) {
            continue;
        }

        if (nothingCrafter()) {
            _productInside = Prefabs::getProduct(getRecipeOutput(ProductType::NOTHING))->getComponent<Product>();
        }
        outputMachine->tryToInsertProduct(glm::vec2(transform->_position.x, transform->_position.z), _productInside);
    }

    _productInside = new Product();
}

bool Machine::anyCrafter() {
    for (int i = 0; i < _craftingRecipes.size(); i++) {
        if (_craftingRecipes[i].getInputProductType() == ProductType::ANY) {
            return true;
        }
    }
    return false;
}

bool Machine::nothingCrafter() {
    for (int i = 0; i < _craftingRecipes.size(); i++) {
        if (_craftingRecipes[i].getInputProductType() == ProductType::NOTHING) {
            return true;
        }
    }
    return false;
}

void Machine::onProductEnter() {
    if (getRecipeOutput(ProductType::ANY) == ProductType::NOTHING) {
        CashManager::updateMoney(_productInside.getPrice());
        _productInside = new Product();
        return;
    }


    _incrementTimer = true;

    GameObject* child = getOwner()->getChild(0);

    if (child != nullptr) {
        child->setActive(true);
    }
}
