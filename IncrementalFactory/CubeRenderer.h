#pragma once
#include "Component.h"

class CubeRenderer : public Component {
private:
    float _size;
public:
    CubeRenderer(float size = 1.0f);

    void render();

    const float& getSize() const;
    void setSize(const float& size);

    Component copy();
};
