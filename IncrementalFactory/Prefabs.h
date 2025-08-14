#pragma once
#include "GameObject.h"
#include "MeshRenderer.h"

static class Prefabs
{
private:
	static std::vector<GameObject> _prefabs;
public:
	static void initPrefabs();
	static GameObject getPrefab(std::string name);
};

