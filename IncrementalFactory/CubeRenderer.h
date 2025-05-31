#pragma once
#include "Renderer.h"

class CubeRenderer : public Renderer {
private:
    float _size;
public:
    CubeRenderer(float size = 1.0f);

    void render();

    const float& getSize() const;
    void setSize(const float& size);
};
