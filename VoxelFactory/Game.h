#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "Dictionary.h"
#include "Dictionary.cpp"

static class Game
{
private:
	static Dictionary<std::string, Scene*> _scenes;
	static Scene* _currentScene;
public:
	static void update();
	static void render();

	static void addObject(GameObject* newObject);
	static void addObject(std::string sceneName, GameObject* newObject);
	static void removeObject(GameObject* objectToRemove);
	static void removeObject(std::string sceneName, GameObject* objectToRemove);

	static void addUIObject(GameObject* newObject);
	static void addUIObject(std::string sceneName, GameObject* newObject);
	static void removeUIObject(GameObject* objectToRemove);
	static void removeUIObject(std::string sceneName, GameObject* objectToRemove);

	static void setCurrentScene(std::string sceneName);
	static void addScene(std::string sceneName);
};

