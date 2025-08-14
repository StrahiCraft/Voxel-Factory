#include "Prefabs.h"

std::vector<GameObject> Prefabs::_prefabs;

void Prefabs::initPrefabs() {
	GameObject placingMachine = GameObject("PlacingMachine", std::vector<GameObject*> {
		new GameObject("PlacementArrow")
	});
	placingMachine.addComponent<MeshRenderer>();
	placingMachine.getComponent<MeshRenderer>()->setMeshRendering(false);
	placingMachine.getChild(0)->addComponent<MeshRenderer>("Models/PlacementArrow/PlacementArrow.obj");

	_prefabs.push_back(placingMachine);
}

GameObject Prefabs::getPrefab(std::string name) {
	/*for (auto& prefab : _prefabs) {
		if (prefab.getName() == name) {
			return GameObject(prefab);
		}
	}*/
	return GameObject("Prefab not found");
}
