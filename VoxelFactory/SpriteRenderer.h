#pragma once
#include "Component.h"
#include "Sprite.h"

class SpriteRenderer :
    public Component
{
private:
    Sprite* _sprite;
    glm::vec3 _color = glm::vec3(1);
public:
    ~SpriteRenderer();
    SpriteRenderer(Sprite* sprite, glm::vec3 color = glm::vec3(1));

    void render();

    Sprite* getSprite();
    void setSprite(Sprite* newSprite);
    void setColor(glm::vec3 color);

    Component* copy();
};

