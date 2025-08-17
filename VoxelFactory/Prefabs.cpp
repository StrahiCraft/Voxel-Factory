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

	initMachines();
}

void Prefabs::initMachines() {
	// ===============================================================================================================
	// MISC
	// ===============================================================================================================

	GameObject conveyor = GameObject("Conveyor");
	conveyor.addComponent<MeshRenderer>("Models/Machines/Conveyor/Conveyor.obj");
	conveyor.addComponent<Machine>(1, std::vector<glm::vec2>{glm::vec2(0, -1)},
		std::vector<glm::vec2>{glm::vec2(0, 1)}, std::vector<CraftingRecipe>{CraftingRecipe(ProductType::ANY, ProductType::ANY)}, 10);
	conveyor.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(conveyor));

	GameObject seller = GameObject("Seller");
	seller.addComponent<MeshRenderer>("Models/Machines/Seller/Seller.obj");
	seller.addComponent<Machine>(1, std::vector<glm::vec2>{
		glm::vec2(0, 1),
			glm::vec2(0, -1),
			glm::vec2(1, 0),
			glm::vec2(-1, 0)}, std::vector<glm::vec2>{},
			std::vector<CraftingRecipe>{CraftingRecipe(ProductType::ANY, ProductType::NOTHING)}, 50);
	seller.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(seller));

	// ===============================================================================================================
	// CRAFTERS
	// ===============================================================================================================

	GameObject furnace = GameObject("Furnace");
	furnace.addComponent<MeshRenderer>("Models/Machines/Furnace/Furnace.obj");
	furnace.addComponent<Machine>(1, std::vector<glm::vec2> {
		glm::vec2(0, -1)}, std::vector<glm::vec2>{glm::vec2(0, 1)},
		std::vector<CraftingRecipe> {
			CraftingRecipe(ProductType::IRON_ORE, ProductType::IRON_INGOT),
			CraftingRecipe(ProductType::CUT_STONE, ProductType::STONE_BRICK)
	}, 300);
	furnace.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(furnace));

	GameObject saw = GameObject("Saw");
	saw.addComponent<MeshRenderer>("Models/Machines/Saw/Saw.obj");
	saw.addComponent<Machine>(1, std::vector<glm::vec2> {
		glm::vec2(0, -1)}, std::vector<glm::vec2>{glm::vec2(0, 1)},
		std::vector<CraftingRecipe> {
			CraftingRecipe(ProductType::LOG, ProductType::STRIPPED_LOG),
			CraftingRecipe(ProductType::STRIPPED_LOG, ProductType::PLANK),
			CraftingRecipe(ProductType::STONE, ProductType::CUT_STONE)
	}, 50);
	saw.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(saw));

	GameObject metalPress = GameObject("Metal press");
	metalPress.addComponent<MeshRenderer>("Models/Machines/MetalPress/MetalPress.obj");
	metalPress.addComponent<Machine>(1, std::vector<glm::vec2>{
		glm::vec2(0, -1)}, std::vector<glm::vec2> {glm::vec2(0, 1)},
			std::vector<CraftingRecipe> {CraftingRecipe(ProductType::IRON_INGOT, ProductType::IRON_PLATE)}, 700);
	metalPress.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(metalPress));

	// ===============================================================================================================
	// PRODUCT GENERATORS
	// ===============================================================================================================

	GameObject ironGenerator = GameObject("Iron generator");
	ironGenerator.addComponent<MeshRenderer>("Models/Machines/IronGenerator/IronGenerator.obj");
	ironGenerator.getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	ironGenerator.addComponent<Machine>(1, std::vector<glm::vec2>{}, std::vector<glm::vec2>{
		glm::vec2(0, 1),
		glm::vec2(0, -1), 
		glm::vec2(1, 0),
		glm::vec2(-1, 0)},
		std::vector<CraftingRecipe> {CraftingRecipe(ProductType::NOTHING, ProductType::IRON_ORE)}, 500);
	ironGenerator.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(ironGenerator));

	GameObject woodGenerator = GameObject("Wood generator");
	woodGenerator.addComponent<MeshRenderer>("Models/Machines/WoodGenerator/WoodGenerator.obj");
	woodGenerator.addComponent<Machine>(1, std::vector<glm::vec2>{}, std::vector<glm::vec2>{
		glm::vec2(0, 1),
		glm::vec2(0, -1),
		glm::vec2(1, 0),
		glm::vec2(-1, 0)},
		std::vector<CraftingRecipe> {CraftingRecipe(ProductType::NOTHING, ProductType::LOG)}, 30);
	woodGenerator.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(woodGenerator));

	GameObject stoneGenerator = GameObject("Stone generator");
	stoneGenerator.addComponent<MeshRenderer>("Models/Machines/StoneGenerator/StoneGenerator.obj");
	stoneGenerator.addComponent<Machine>(1, std::vector<glm::vec2>{}, std::vector<glm::vec2>{
		glm::vec2(0, 1),
		glm::vec2(0, -1),
		glm::vec2(1, 0),
		glm::vec2(-1, 0)},
		std::vector<CraftingRecipe> {CraftingRecipe(ProductType::NOTHING, ProductType::STONE)}, 100);
	stoneGenerator.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(stoneGenerator));
}

GameObject* Prefabs::getPrefab(std::string name) {
	for (auto& prefab : _prefabs) {
		if (prefab.getName() == name) {
			return new GameObject(prefab);
		}
	}
	return new GameObject("Prefab not found");
}
