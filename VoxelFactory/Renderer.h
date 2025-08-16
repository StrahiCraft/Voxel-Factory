#pragma once
#include "Component.h"

class Renderer : public Component {
public:
    virtual void render() = 0;
};