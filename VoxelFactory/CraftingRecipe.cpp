#include "CraftingRecipe.h"

CraftingRecipe::CraftingRecipe(ProductType input, ProductType output) {
	_input = input;
	_output = output;
}

ProductType CraftingRecipe::getInputProductType() {
	return _input;
}

ProductType CraftingRecipe::getOutputProductType() {
	return _output;
}
