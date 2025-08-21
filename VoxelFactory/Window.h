#pragma once
#include "glut.h"
#include "glm.hpp"

static class Window {
private:
	static glm::vec2 _windowSize;

public:
	static void reshape(int x, int y);
	static glm::vec2 getWindowSize();
	static void updateWindow();
};

