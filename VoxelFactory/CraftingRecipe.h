#pragma once
#include <vector>
#include "ProductType.h"
class CraftingRecipe {
private:
	ProductType _input;
	ProductType _output;

public:
	CraftingRecipe(ProductType input, ProductType output);

	ProductType getInputProductType();
	ProductType getOutputProductType();
};

