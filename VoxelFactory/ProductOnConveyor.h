#pragma once
#include "Machine.h"
#include "Prefabs.h"

class ProductOnConveyor :
    public Component
{
private:
    Machine* _conveyor;
    ProductType _currentType;
public:
    ProductOnConveyor(Machine* conveyor);

    void update();

    Component* copy();
};

