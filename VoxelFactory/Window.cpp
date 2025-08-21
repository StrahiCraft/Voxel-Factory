#include "Window.h"

glm::vec2 Window::_windowSize = { 1280, 720 };

void Window::reshape(int x, int y) {
	_windowSize = glm::vec2(x, y);
	
	updateWindow();
}

glm::vec2 Window::getWindowSize()
{
	return _windowSize;
}

void Window::updateWindow() {
	glutReshapeWindow(_windowSize.x, _windowSize.y);
	glViewport(0, 0, _windowSize.x, _windowSize.y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, float(_windowSize.x) / float(_windowSize.y), 0.1f, 300.0f);
	glMatrixMode(GL_MODELVIEW);
}
