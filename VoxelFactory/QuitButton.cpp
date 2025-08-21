#include "QuitButton.h"

QuitButton::QuitButton(glm::vec2 bounds, glm::vec3 color) : Button(bounds, color){
}

void QuitButton::onButtonClicked() {
	exit(0);
}