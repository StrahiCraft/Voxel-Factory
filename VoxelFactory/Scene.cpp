#include "Scene.h"

void Scene::update() {
	for (int i = 0; i < _objects.size(); i++) {
		_objects[i]->update();
	}

	for (int i = 0; i < _uiObjects.size(); i++) {
		_uiObjects[i]->update();
	}
}

void Scene::render() {
	render3D();

	render2D();
}

void Scene::render3D() {
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

void Scene::render2D() {
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

void Scene::addObject(GameObject* newObject) {
	_objects.push_back(newObject);
}

void Scene::removeObject(GameObject* objectToRemove) {
	_objects.erase(std::remove(_objects.begin(), _objects.end(), objectToRemove), _objects.end());
}

void Scene::addUIObject(GameObject* newObject) {
	_uiObjects.push_back(newObject);
}

void Scene::removeUIObject(GameObject* objectToRemove) {
	_uiObjects.erase(std::remove(_uiObjects.begin(), _uiObjects.end(), objectToRemove), _uiObjects.end());
}
