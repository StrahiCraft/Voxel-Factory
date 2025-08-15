#include "Prefabs.h"

std::vector<GameObject> Prefabs::_prefabs;

void Prefabs::initPrefabs() {
	GameObject placingMachine = GameObject("PlacingMachine", std::vector<GameObject*> {
		new GameObject("PlacementArrow")
	});
	placingMachine.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	placingMachine.setIgnoreParentTransform(true);
	placingMachine.addComponent<MeshRenderer>("Models/Machines/Conveyor/Conveyor.obj");
	placingMachine.getComponent<MeshRenderer>()->setMeshRendering(false);
	placingMachine.getComponent<MeshRenderer>()->setSelected(true);
	placingMachine.getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(0, 1, 0));
	placingMachine.getChild(0)->addComponent<MeshRenderer>("Models/PlacementArrow/PlacementArrow.obj");
	placingMachine.getChild(0)->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));

	_prefabs.push_back(GameObject(placingMachine));

	// =======================================================================================================

	GameObject conveyor = GameObject("Conveyor");
	conveyor.addComponent<MeshRenderer>("Models/Machines/Conveyor/Conveyor.obj");
	conveyor.addComponent<Machine>(1, glm::vec2(0), glm::vec2(0, -1), glm::vec2(0, 1), CraftingRecipe(ProductType::ANY, ProductType::ANY));
	conveyor.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);

	_prefabs.push_back(GameObject(conveyor));
}

GameObject* Prefabs::getPrefab(std::string name) {
	for (auto& prefab : _prefabs) {
		if (prefab.getName() == name) {
			return new GameObject(prefab);
		}
	}
	return new GameObject("Prefab not found");
}
