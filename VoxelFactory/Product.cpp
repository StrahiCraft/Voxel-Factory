#include "Product.h"

Product::Product() {
	_price = 0;
	_type = ProductType::NOTHING;
}

Product::Product(double price, ProductType type) {
	_price = price;
	_type = type;
}

Product::Product(Product* other) {
	_price = other->getPrice();
	_type = other->getType();
}

double Product::getPrice() const {
	return _price;
}

ProductType Product::getType() const {
	return _type;
}

Component* Product::copy() {
	return new Product(_price, _type);
}