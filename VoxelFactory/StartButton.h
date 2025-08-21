#pragma once
#include "Button.h"
#include "Game.h"
class StartButton :
    public Button
{
public:
    StartButton(glm::vec2 bounds = glm::vec2(100), glm::vec3 color = glm::vec3(1));
    void onButtonClicked();
};

