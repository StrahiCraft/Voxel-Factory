#pragma once
#include "GameObject.h"
#include "ScreenAlignment.h"
#include "Window.h"

class UIObject :
    public GameObject
{
private:
    ScreenAlignment _screenAlignment;
public:
    UIObject(const std::string& name = "UIObject", ScreenAlignment screenAlignment = ScreenAlignment::CENTER,
        std::vector<UIObject*> children = {});
    UIObject(UIObject* other);

    void render();

private:
    void align();
};

