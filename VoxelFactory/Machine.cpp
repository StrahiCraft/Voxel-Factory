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
    if (product.getType() == ProductType::NOTHING) {
        return false;
    }

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
            _productsInside.setValue(product.getType(), _productsInside.getValue(product.getType()) + 1);
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

UIObject* Machine::createCraftingRecipeUI() {
    UIObject* craftingRecipes = new UIObject("CraftingRecipes", ScreenAlignment::TOP_LEFT);

    if (anyCrafter() || nothingCrafter() || seller()) {
        return craftingRecipes;
    }
    
    int verticalOffset = 0;
    craftingRecipes->getComponent<Transform>()->_position = glm::vec3(84, -160, 0);

    for (int i = 0; i < _craftingRecipes.size(); i++) {
        craftingRecipes->addChild(new UIObject("Recipe " + std::to_string(i)));
        craftingRecipes->getChild(i)->getComponent<Transform>()->_position.y = verticalOffset;
        int horizotnalOffset = 0;

        int j;
        for (j = 0; j < _craftingRecipes[i].getInputProductTypes().size(); j++) {
            craftingRecipes->getChild(i)->addChild(new UIObject("RecipeInput" + j));
            craftingRecipes->getChild(i)->getChild(j * 2)->addComponent<SpriteRenderer>(
                Prefabs::getProduct(_craftingRecipes[i].getInputProductTypes()[j])->getComponent<SpriteRenderer>()->getSprite());
            craftingRecipes->getChild(i)->getChild(j * 2)->getComponent<Transform>()->_position.x = horizotnalOffset;

            horizotnalOffset += 64;

            craftingRecipes->getChild(i)->addChild(new UIObject("Sign"));
            craftingRecipes->getChild(i)->getChild(j * 2 + 1)->addComponent<SpriteRenderer>(
                new Sprite("Sprites/font.png", glm::vec2(64), 1, glm::vec2(15, 8), true));
            if (_craftingRecipes[i].getInputProductTypes().size() - (j + 1) == 0) {
                craftingRecipes->getChild(i)->getChild(j * 2 + 1)->getComponent<SpriteRenderer>()->getSprite()->setCurrentFrame('>' - 32);
            }
            else {
                craftingRecipes->getChild(i)->getChild(j * 2 + 1)->getComponent<SpriteRenderer>()->getSprite()->setCurrentFrame('+' - 32);
            }
            craftingRecipes->getChild(i)->getChild(j * 2 + 1)->getComponent<SpriteRenderer>()->getSprite()->setSpriteFlip(glm::vec2(1, 0));
            craftingRecipes->getChild(i)->getChild(j * 2 + 1)->getComponent<Transform>()->_position = glm::vec3(horizotnalOffset - 8, 8, 0);
            craftingRecipes->getChild(i)->getChild(j * 2 + 1)->getComponent<Transform>()->_scale = glm::vec3(0.75f);

            horizotnalOffset += 64;
        }
        craftingRecipes->getChild(i)->addChild(new UIObject("RecipeOutput"));
        craftingRecipes->getChild(i)->getChild(j * 2)->addComponent<SpriteRenderer>(
            Prefabs::getProduct(_craftingRecipes[i].getOutputProductType())->getComponent<SpriteRenderer>()->getSprite());
        craftingRecipes->getChild(i)->getChild(j * 2)->getComponent<Transform>()->_position.x = horizotnalOffset;

        verticalOffset -= 74;
    }

    return craftingRecipes;
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
    Transform* transform = getOwner()->getComponent<Transform>();

    if (_output.getType() == ProductType::NOTHING) {
        _output = craft();
    }

    _tryingToOutput = true;

    if (_output.getType() == ProductType::NOTHING) {
        return;
    }


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

bool Machine::seller() {
    return getRecipeOutput(ProductType::ANY) == ProductType::NOTHING;
}

void Machine::onProductEnter() {
    if (seller()) {
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

Component* Machine::copy() {
    return new Machine(_delay, _inputDirections, _outputDirections, _craftingRecipes, _price, _maxProductTypes, _maxProductsPerType);
}