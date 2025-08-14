#include "CraftingRecipe.h"

CraftingRecipe::CraftingRecipe(std::vector<ProductType> input, ProductType output) {
	_input = input;
	_output = output;
}

CraftingRecipe::CraftingRecipe(ProductType input, ProductType output) {
	_input.push_back(input);
	_output = output;
}
