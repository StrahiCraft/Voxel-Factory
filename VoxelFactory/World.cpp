#include "World.h"

std::vector<GameObject*> World::_objects;
std::vector<GameObject*> World::_uiObjects;

void World::update() {
	for (int i = 0; i < _objects.size(); i++) {
		_objects[i]->update();
	}

	for (int i = 0; i < _uiObjects.size(); i++) {
		_uiObjects[i]->update();
	}
}

void World::render() {
	render3D();

	render2D();
}

void World::render3D() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);

	for (int i = 0; i < _objects.size(); i++) {
		_objects[i]->render();
	}

	glPopMatrix();
	glPopAttrib();
}

void World::render2D() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMultMatrixf(glm::value_ptr(glm::ortho(0.0f, (float)glutGet(GLUT_WINDOW_WIDTH), 0.0f, (float)glutGet(GLUT_WINDOW_HEIGHT), -1.0f, 1.0f)));

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);

	for (int i = 0; i < _uiObjects.size(); i++) {
		_uiObjects[i]->render();
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glPopAttrib();
}

void World::addObject(GameObject* newObject) {
	_objects.push_back(newObject);
}

void World::removeObject(GameObject* objectToRemove) {
	_objects.erase(std::remove(_objects.begin(), _objects.end(), objectToRemove), _objects.end());
}

void World::addUIObject(GameObject* newObject) {
	_uiObjects.push_back(newObject);
}

void World::removeUIObject(GameObject* objectToRemove) {
	_uiObjects.erase(std::remove(_uiObjects.begin(), _uiObjects.end(), objectToRemove), _uiObjects.end());
}

void World::printWorld() {
	for (int i = 0; i < _objects.size(); i++) {
		_objects[i]->printChildren();
		std::cout << std::endl;
	}
}

