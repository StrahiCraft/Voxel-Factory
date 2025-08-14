#include "Product.h"

Product::Product(double price, ProductType type) {
	_price = price;
	_type = type;
}

double Product::getPrice() const {
	return _price;
}

ProductType Product::getType() const {
	return _type;
}