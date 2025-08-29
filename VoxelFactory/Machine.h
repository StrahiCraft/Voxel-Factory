#pragma once
#include "Component.h"
#include "CraftingRecipe.h"
#include "Product.h"
#include "Direction.h"
#include "Dictionary.h"
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
    Dictionary<ProductType, int> _productsInside;
    int _maxProductTypes;
    int _maxProductsPerType;

    Product _output;

    int _price;

    bool _tryingToOutput = false;
public:
    Machine(float delay, std::vector<Direction> inputDirections, std::vector<Direction> outputDirections,
        std::vector<CraftingRecipe> craftingRecipes, int price, int maxProductTypes = 1, int maxProductsPerType = 1);

    void update();

    int getPrice();
    ProductType getProductType();

    bool tryToInsertProduct(glm::vec2 insertPoint, Product product);

    float getCraftingCompletionAmount();

    Component* copy();
private:
    bool insertProduct(Product product);
    bool hasSpaceForProduct(Product product);

    bool productValidForCrafting(Product product);
    bool productFromValidDirection(glm::vec2 insertPoint);

    Direction directionFromPoint(glm::vec2 point);
    glm::vec3 pointFromDirection(Direction direction);

    ProductType getRecipeOutput(ProductType input);
    ProductType getRecipeOutput(std::vector<ProductType> input);

    Product craft();
    bool canCraft(CraftingRecipe recipe);
    void removeItemsFromRecipe(CraftingRecipe recipe);
    void outputNewProduct();

    bool anyCrafter();
    bool nothingCrafter();

    void onProductEnter();
};