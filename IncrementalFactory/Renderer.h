#pragma once
#include "Component.h"
#include "Mesh.h"

class Renderer : public Component {
public:
    virtual void render() = 0;
};