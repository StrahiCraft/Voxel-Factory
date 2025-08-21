#pragma once
#include "Button.h"
class QuitButton :
    public Button
{
public:
    QuitButton(glm::vec2 bounds = glm::vec2(100), glm::vec3 color = glm::vec3(1));
    void onButtonClicked();
};

