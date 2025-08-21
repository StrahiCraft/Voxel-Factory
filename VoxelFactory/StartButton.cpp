#include "StartButton.h"

StartButton::StartButton(glm::vec2 bounds, glm::vec3 color) : Button(bounds, color)
{
}

void StartButton::onButtonClicked() {
	Game::setCurrentScene("Factory");
}
