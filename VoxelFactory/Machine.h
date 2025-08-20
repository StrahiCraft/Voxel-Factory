#pragma once
#include "Component.h"
#include "CraftingRecipe.h"
#include "Product.h"
#include "Direction.h"
#include "Prefabs.h"
#include "CashManager.h"

class Machine :
    public Component
{
private:
    float _delay;
    float _timer = 0;
    bool _incrementTimer = false;

    std::vector<Direction> _inputDirections;
    std::vector<Direction> _outputDirections;

    std::vector<CraftingRecipe> _craftingRecipes;
    Product _productInside;

    int _price;
public:
    Machine(float delay, std::vector<Direction> inputDirections, std::vector<Direction> outputDirections,
        std::vector<CraftingRecipe> craftingRecipes, int price);

    void update();

    int getPrice();
    void tryToInsertProduct(glm::vec2 insertPoint, Product product);

    Component* copy();
private:
    bool productValidForCrafting(Product product);
    bool productFromValidDirection(glm::vec2 insertPoint);
    Direction directionFromPoint(glm::vec2 point);
    glm::vec3 pointFromDirection(Direction direction);
    ProductType getRecipeOutput(ProductType input);
    void craftNewProduct();

    bool anyCrafter();
    bool nothingCrafter();
protected:
    void onProductEnter();
};