#pragma once
#include <vector>
#include "ProductType.h"
class CraftingRecipe {
private:
	ProductType _input;
	ProductType _output;
	float _successChance;
public:
	CraftingRecipe(ProductType input, ProductType output, float successChance = 1.0f);
	CraftingRecipe(std::vector<ProductType> inputs, ProductType output, float successChance = 1.0f);

	ProductType getInputProductType();
	ProductType getOutputProductType();
};

