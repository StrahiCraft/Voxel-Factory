#pragma once
#include <vector>
#include "ProductType.h"
class CraftingRecipe {
private:
	std::vector<ProductType> _input;
	ProductType _output;
	float _successChance;
public:
	CraftingRecipe(ProductType input, ProductType output, float successChance = 1.0f);
	CraftingRecipe(std::vector<ProductType> input, ProductType output, float successChance = 1.0f);

	std::vector<ProductType> getInputProductTypes();
	ProductType getOutputProductType();
};

