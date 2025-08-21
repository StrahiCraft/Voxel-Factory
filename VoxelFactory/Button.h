#pragma once
#include "Component.h"
#include "Input.h"
class Button :
    public Component
{
private:
    glm::vec2 _bounds;
    glm::vec3 _color;

public:
    Button(glm::vec2 bounds = glm::vec2(100), glm::vec3 color = glm::vec3(1));

    void update();
    void render();

    Component* copy();

protected:
    virtual void onButtonClicked();

private:
    bool mouseInBounds();
};

