#pragma once
#include "Component.h"

class ConeRenderer : public Component {
private:
    float _base;
    float _height;

    int _slices;
    int _stacks;
public:
    ConeRenderer(float base = 1.0f, float height = 2.0f, int slices = 16, int stacks = 16);

    void render();

    const float& getBase() const;
    void setBase(const float& base);

    const float& getHeight() const;
    void setHeight(const float& height);

    const int& getSlices() const;
    void setSlices(const int& slices);

    const int& getStacks() const;
    void setStacks(const int& stacks);
};