#pragma once
#include <vector>
#include "ProductType.h"
class CraftingRecipe {
private:
	std::vector<ProductType> _input;
	ProductType _output;

public:
	CraftingRecipe(std::vector<ProductType> input, ProductType output);
	CraftingRecipe(ProductType input, ProductType output);
};

