#pragma once
#include "Renderer.h"

class SphereRenderer : public Renderer {
private:
    float _radius;

    int _slices;
    int _stacks;
public:
    SphereRenderer(float radius = 1.0f, int slices = 16, int stacks = 16);

    void render();

    const float& getRadius() const;
    void setRadius(const float& radius);

    const int& getSlices() const;
    void setSlices(const int& slices);

    const int& getStacks() const;
    void setStacks(const int& stacks);
};