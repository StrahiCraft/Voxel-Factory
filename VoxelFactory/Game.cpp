#include "Game.h"
#include "UIObject.h"

Dictionary<std::string, Scene*> Game::_scenes;
Scene* Game::_currentScene;

void Game::update() {
	_currentScene->update();
}

void Game::render() {
	_currentScene->render();
}

void Game::addObject(GameObject* newObject) {
	_currentScene->addObject(newObject);
}

void Game::addObject(std::string sceneName, GameObject* newObject) {
	_scenes.getValue(sceneName)->addObject(newObject);
}

void Game::removeObject(GameObject* objectToRemove) {
	_currentScene->removeObject(objectToRemove);
}

void Game::removeObject(std::string sceneName, GameObject* objectToRemove) {
	_scenes.getValue(sceneName)->removeObject(objectToRemove);
}

void Game::addUIObject(UIObject* newObject) {
	_currentScene->addUIObject(newObject);
}

void Game::addUIObject(std::string sceneName, UIObject* newObject) {
	_scenes.getValue(sceneName)->addUIObject(newObject);
}

void Game::removeUIObject(UIObject* objectToRemove) {
	_currentScene->removeUIObject(objectToRemove);
}

void Game::removeUIObject(std::string sceneName, UIObject* objectToRemove) {
	_scenes.getValue(sceneName)->removeUIObject(objectToRemove);
}

void Game::setCurrentScene(std::string sceneName) {
	_currentScene = _scenes.getValue(sceneName);
}

void Game::addScene(std::string sceneName) {
	_scenes.addItem(sceneName, new Scene());
}