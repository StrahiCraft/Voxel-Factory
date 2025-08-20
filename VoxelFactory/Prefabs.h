#pragma once
#include "GameObject.h"
#include "Machine.h"
#include "MeshRenderer.h"

static class Prefabs
{
private:
	static std::vector<GameObject> _prefabs;
	static std::vector<GameObject> _products;
public:
	static void initPrefabs();

	static GameObject* getPrefab(std::string name);
	static GameObject* getProduct(ProductType type);
private:
	static void initMachines();
	static void initProducts();
};

