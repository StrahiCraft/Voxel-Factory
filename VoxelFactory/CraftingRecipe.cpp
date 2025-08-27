#include "CraftingRecipe.h"

CraftingRecipe::CraftingRecipe(ProductType input, ProductType output, float successChance) {
	_input = input;
	//_input.push_back(input);
	_output = output;
	_successChance = successChance;
}

CraftingRecipe::CraftingRecipe(std::vector<ProductType> input, ProductType output, float successChance) {
	//_input = input;
	_output = output;
	_successChance = successChance;
}

ProductType CraftingRecipe::getInputProductType() {
	return _input;
}

ProductType CraftingRecipe::getOutputProductType() {
	return _output;
}
