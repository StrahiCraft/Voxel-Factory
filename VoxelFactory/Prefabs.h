#pragma once
#include "GameObject.h"
#include "Machine.h"
#include "MeshRenderer.h"

static class Prefabs
{
private:
	static std::vector<GameObject> _prefabs;
public:
	static void initPrefabs();
	static void initMachines();

	static GameObject* getPrefab(std::string name);
};

