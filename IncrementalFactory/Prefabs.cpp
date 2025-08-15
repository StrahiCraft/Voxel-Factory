#include "Prefabs.h"

std::vector<GameObject> Prefabs::_prefabs;

void Prefabs::initPrefabs() {
	GameObject placingMachine = GameObject("PlacingMachine", std::vector<GameObject*> {
		new GameObject("PlacementArrow")
	});
	placingMachine.getComponent<Transform>()->scale = glm::vec3(1 / 1.6f);
	placingMachine.setIgnoreParentTransform(true);
	placingMachine.addComponent<MeshRenderer>("Models/Machines/Conveyor/Conveyor.obj");
	placingMachine.getComponent<MeshRenderer>()->setMeshRendering(false);
	placingMachine.getComponent<MeshRenderer>()->setSelected(true);
	placingMachine.getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(0, 1, 0));
	placingMachine.getChild(0)->addComponent<MeshRenderer>("Models/PlacementArrow/PlacementArrow.obj");

	_prefabs.push_back(GameObject(placingMachine));
}

GameObject Prefabs::getPrefab(std::string name) {
	for (auto prefab : _prefabs) {
		if (prefab.getName() == name) {
			return GameObject(prefab);
		}
	}
	return GameObject("Prefab not found");
}
