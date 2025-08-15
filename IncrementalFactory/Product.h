#pragma once
#include "Component.h"
#include "ProductType.h"
class Product :
    public Component
{
private:
    double _price = 0;
    ProductType _type;

public:
    Product(double price, ProductType type);
    double getPrice() const;
    ProductType getType() const;

    Component* copy();
};