#include "Prefabs.h"
#include "ProductOnConveyor.h"

std::vector<GameObject> Prefabs::_prefabs;
std::vector<GameObject> Prefabs::_products;

void Prefabs::initPrefabs() {
	GameObject placingMachine = GameObject("PlacingMachine", std::vector<GameObject*> {
		new GameObject("PlacementArrow")
	});
	placingMachine.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	placingMachine.addComponent<MeshRenderer>("Models/Machines/Conveyor/Conveyor.obj");
	placingMachine.getComponent<MeshRenderer>()->setMeshRendering(false);
	placingMachine.getComponent<MeshRenderer>()->setSelected(true);
	placingMachine.getComponent<MeshRenderer>()->setSelectionColor(glm::vec3(0, 1, 0));
	placingMachine.getChild(0)->addComponent<MeshRenderer>("Models/PlacementArrow/PlacementArrow.obj");
	placingMachine.getChild(0)->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	
	_prefabs.push_back(GameObject(placingMachine));

	// =======================================================================================================

	initMachines();
	initProducts();
}

void Prefabs::initMachines() {
	// ===============================================================================================================
	// MISC
	// ===============================================================================================================

	GameObject conveyor = GameObject("Conveyor", std::vector<GameObject*> {new GameObject("ProductOnConveyor")});
	conveyor.addComponent<MeshRenderer>("Models/Machines/Conveyor/Conveyor.obj");
	conveyor.addComponent<Machine>(1, std::vector<Direction>{
		Direction::BACK,
		Direction::LEFT,
		Direction::RIGHT},
		std::vector<Direction>{Direction::FORWARD}, std::vector<CraftingRecipe>{CraftingRecipe(ProductType::ANY, ProductType::ANY)}, 10);
	conveyor.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);

	conveyor.getChild(0)->getComponent<Transform>()->_position.y = 0.7f;
	conveyor.getChild(0)->addComponent<MeshRenderer>();
	conveyor.getChild(0)->addComponent<ProductOnConveyor>(conveyor.getComponent<Machine>());
	conveyor.getChild(0)->setActive(false);

	_prefabs.push_back(GameObject(conveyor));

	GameObject seller = GameObject("Seller");
	seller.addComponent<MeshRenderer>("Models/Machines/Seller/Seller.obj");
	seller.addComponent<Machine>(0, std::vector<Direction>{
		Direction::FORWARD,
		Direction::BACK,
		Direction::LEFT,
		Direction::RIGHT}, std::vector<Direction>{},
			std::vector<CraftingRecipe>{CraftingRecipe(ProductType::ANY, ProductType::NOTHING)}, 50);
	seller.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(seller));

	// ===============================================================================================================
	// CRAFTERS
	// ===============================================================================================================

	GameObject furnace = GameObject("Furnace");
	furnace.addComponent<MeshRenderer>("Models/Machines/Furnace/Furnace.obj");
	furnace.addComponent<Machine>(5, std::vector<Direction> {
		Direction::BACK}, std::vector<Direction>{Direction::FORWARD},
		std::vector<CraftingRecipe> {
			CraftingRecipe(ProductType::WOOD, ProductType::CHARCOAL),
			CraftingRecipe(ProductType::CUT_STONE, ProductType::STONE_BRICK),
			CraftingRecipe(ProductType::COPPER_ORE, ProductType::COPPER_INGOT),
			CraftingRecipe(ProductType::IRON_ORE, ProductType::IRON_INGOT),
			CraftingRecipe(ProductType::GOLD_ORE, ProductType::GOLD_INGOT),
	}, 300);
	furnace.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(furnace));

	GameObject saw = GameObject("Saw", std::vector<GameObject*> {new GameObject("ProductOnConveyor")});
	saw.addComponent<MeshRenderer>("Models/Machines/Saw/Saw.obj");
	saw.addComponent<Machine>(2, std::vector<Direction> {
		Direction::BACK}, std::vector<Direction>{Direction::FORWARD},
		std::vector<CraftingRecipe> {
			CraftingRecipe(ProductType::WOOD, ProductType::STRIPPED_LOG),
			CraftingRecipe(ProductType::STRIPPED_LOG, ProductType::PLANK),
			CraftingRecipe(ProductType::STONE, ProductType::CUT_STONE),
			CraftingRecipe(ProductType::COPPER_INGOT, ProductType::CUT_COPPER),
			CraftingRecipe(ProductType::GOLD_INGOT, ProductType::CUT_GOLD),
	}, 50);
	saw.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);

	saw.getChild(0)->getComponent<Transform>()->_position.y = 0.7f;
	saw.getChild(0)->addComponent<MeshRenderer>();
	saw.getChild(0)->addComponent<ProductOnConveyor>(saw.getComponent<Machine>());
	saw.getChild(0)->setActive(false);

	_prefabs.push_back(GameObject(saw));

	GameObject metalPress = GameObject("Metal press", std::vector<GameObject*> {new GameObject("ProductOnConveyor")});
	metalPress.addComponent<MeshRenderer>("Models/Machines/MetalPress/MetalPress.obj");
	metalPress.addComponent<Machine>(2.5f, std::vector<Direction>{
		Direction::BACK}, std::vector<Direction> {Direction::FORWARD},
			std::vector<CraftingRecipe> {
			CraftingRecipe(ProductType::IRON_INGOT, ProductType::IRON_PLATE),
			CraftingRecipe(ProductType::COPPER_INGOT, ProductType::COPPER_PLATE),
			CraftingRecipe(ProductType::GOLD_INGOT, ProductType::GOLD_PLATE),
			CraftingRecipe(ProductType::ROSE_GOLD_INGOT, ProductType::ROSE_GOLD_PLATE),
		}, 700);
	metalPress.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);

	metalPress.getChild(0)->getComponent<Transform>()->_position.y = 0.7f;
	metalPress.getChild(0)->addComponent<MeshRenderer>();
	metalPress.getChild(0)->addComponent<ProductOnConveyor>(metalPress.getComponent<Machine>());
	metalPress.getChild(0)->setActive(false);

	_prefabs.push_back(GameObject(metalPress));

	// ===============================================================================================================
	// MULTI CRAFTERS
	// ===============================================================================================================

	GameObject mixer = GameObject("Mixer", std::vector<GameObject*> {new GameObject("ProductOnConveyor")});
	saw.addComponent<MeshRenderer>("Models/Machines/Mixer/Mixer.obj");
	saw.addComponent<Machine>(2, std::vector<Direction> { Direction::BACK, Direction::LEFT, Direction::RIGHT},
		std::vector<Direction>{Direction::FORWARD},
			std::vector<CraftingRecipe> {
			CraftingRecipe(std::vector<ProductType> {ProductType::COPPER_INGOT, ProductType::GOLD_INGOT},
				ProductType::ROSE_GOLD_INGOT),
		}, 1000);

	// ===============================================================================================================
	// PRODUCT GENERATORS
	// ===============================================================================================================

	GameObject ironGenerator = GameObject("Iron generator");
	ironGenerator.addComponent<MeshRenderer>("Models/Machines/IronGenerator/IronGenerator.obj");
	ironGenerator.getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	ironGenerator.addComponent<Machine>(10, std::vector<Direction>{}, std::vector<Direction>{
		Direction::FORWARD,
		Direction::BACK,
		Direction::LEFT,
		Direction::RIGHT},
		std::vector<CraftingRecipe> {CraftingRecipe(ProductType::NOTHING, ProductType::IRON_ORE)}, 500);
	ironGenerator.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(ironGenerator));

	GameObject copperGenerator = GameObject("Copper generator");
	copperGenerator.addComponent<MeshRenderer>("Models/Machines/CopperGenerator/CopperGenerator.obj");
	copperGenerator.getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	copperGenerator.addComponent<Machine>(10, std::vector<Direction>{}, std::vector<Direction>{
		Direction::FORWARD,
			Direction::BACK,
			Direction::LEFT,
			Direction::RIGHT},
		std::vector<CraftingRecipe> {CraftingRecipe(ProductType::NOTHING, ProductType::COPPER_ORE)}, 230);
	copperGenerator.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(copperGenerator));

	GameObject goldGenerator = GameObject("Gold generator");
	goldGenerator.addComponent<MeshRenderer>("Models/Machines/GoldGenerator/GoldGenerator.obj");
	goldGenerator.getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	goldGenerator.addComponent<Machine>(10, std::vector<Direction>{}, std::vector<Direction>{
		Direction::FORWARD,
			Direction::BACK,
			Direction::LEFT,
			Direction::RIGHT},
		std::vector<CraftingRecipe> {CraftingRecipe(ProductType::NOTHING, ProductType::GOLD_ORE)}, 1500);
	goldGenerator.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(goldGenerator));

	GameObject woodGenerator = GameObject("Wood generator");
	woodGenerator.addComponent<MeshRenderer>("Models/Machines/WoodGenerator/WoodGenerator.obj");
	woodGenerator.addComponent<Machine>(4, std::vector<Direction>{}, std::vector<Direction>{
		Direction::FORWARD,
		Direction::BACK,
		Direction::LEFT,
		Direction::RIGHT},
		std::vector<CraftingRecipe> {CraftingRecipe(ProductType::NOTHING, ProductType::WOOD)}, 30);
	woodGenerator.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(woodGenerator));

	GameObject stoneGenerator = GameObject("Stone generator");
	stoneGenerator.addComponent<MeshRenderer>("Models/Machines/StoneGenerator/StoneGenerator.obj");
	stoneGenerator.addComponent<Machine>(6.5f, std::vector<Direction>{}, std::vector<Direction>{
		Direction::FORWARD,
		Direction::BACK,
		Direction::LEFT,
		Direction::RIGHT},
		std::vector<CraftingRecipe> {CraftingRecipe(ProductType::NOTHING, ProductType::STONE)}, 100);
	stoneGenerator.getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	_prefabs.push_back(GameObject(stoneGenerator));
}

void Prefabs::initProducts() {
	// ===============================================================================================================
	// WOOD
	// ===============================================================================================================

	GameObject wood = GameObject("Wood");
	wood.addComponent<MeshRenderer>("Models/Product/Wood/Wood.obj");
	wood.addComponent<Product>(3, ProductType::WOOD);
	_products.push_back(wood);

	GameObject strippedLog = GameObject("Stripped log");
	strippedLog.addComponent<MeshRenderer>("Models/Product/StrippedLog/StrippedLog.obj");
	strippedLog.addComponent<Product>(6, ProductType::STRIPPED_LOG);
	_products.push_back(strippedLog);

	GameObject plank = GameObject("Plank");
	plank.addComponent<MeshRenderer>("Models/Product/Plank/Plank.obj");
	plank.addComponent<Product>(10, ProductType::PLANK);
	_products.push_back(plank);

	GameObject charcoal = GameObject("Charcoal");
	charcoal.addComponent<MeshRenderer>("Models/Product/Charcoal/Charcoal.obj");
	charcoal.addComponent<Product>(10, ProductType::CHARCOAL);
	_products.push_back(charcoal);

	// ===============================================================================================================
	// STONE
	// ===============================================================================================================

	GameObject stone = GameObject("Stone");
	stone.addComponent<MeshRenderer>("Models/Product/Stone/Stone.obj");
	stone.addComponent<Product>(5, ProductType::STONE);
	_products.push_back(stone);

	GameObject cutStone = GameObject("Cut stone");
	cutStone.addComponent<MeshRenderer>("Models/Product/CutStone/CutStone.obj");
	cutStone.addComponent<Product>(10, ProductType::CUT_STONE);
	_products.push_back(cutStone);

	GameObject stoneBrick = GameObject("Stone bick");
	stoneBrick.addComponent<MeshRenderer>("Models/Product/StoneBrick/StoneBrick.obj");
	stoneBrick.addComponent<Product>(16, ProductType::STONE_BRICK);
	_products.push_back(stoneBrick);

	// ===============================================================================================================
	// IRON
	// ===============================================================================================================

	GameObject ironOre = GameObject("Iron ore");
	ironOre.addComponent<MeshRenderer>("Models/Product/IronOre/IronOre.obj");
	ironOre.addComponent<Product>(20, ProductType::IRON_ORE);
	_products.push_back(ironOre);

	GameObject ironIngot = GameObject("Iron ingot");
	ironIngot.addComponent<MeshRenderer>("Models/Product/IronIngot/IronIngot.obj");
	ironIngot.addComponent<Product>(35, ProductType::IRON_INGOT);
	_products.push_back(ironIngot);

	GameObject ironPlate = GameObject("Iron plate");
	ironPlate.addComponent<MeshRenderer>("Models/Product/IronPlate/IronPlate.obj");
	ironPlate.addComponent<Product>(60, ProductType::IRON_PLATE);
	_products.push_back(ironPlate);

	// ===============================================================================================================
	// COPPER
	// ===============================================================================================================

	GameObject copperOre = GameObject("Copper ore");
	copperOre.addComponent<MeshRenderer>("Models/Product/CopperOre/CopperOre.obj");
	copperOre.addComponent<Product>(10, ProductType::COPPER_ORE);
	_products.push_back(copperOre);

	GameObject copperIngot = GameObject("Copper ingot");
	copperIngot.addComponent<MeshRenderer>("Models/Product/CopperIngot/CopperIngot.obj");
	copperIngot.addComponent<Product>(20, ProductType::COPPER_INGOT);
	_products.push_back(copperIngot);

	GameObject copperPlate = GameObject("Copper plate");
	copperPlate.addComponent<MeshRenderer>("Models/Product/CopperPlate/CopperPlate.obj");
	copperPlate.addComponent<Product>(35, ProductType::COPPER_PLATE);
	_products.push_back(copperPlate);

	GameObject cutCopper = GameObject("Cut copper");
	cutCopper.addComponent<MeshRenderer>("Models/Product/CutCopper/CutCopper.obj");
	cutCopper.addComponent<Product>(15, ProductType::CUT_COPPER);
	_products.push_back(cutCopper);

	GameObject copperWire = GameObject("Copper wire");
	copperWire.addComponent<MeshRenderer>("Models/Product/CopperWire/CopperWire.obj");
	copperWire.addComponent<Product>(100, ProductType::COPPER_WIRE);
	_products.push_back(copperWire);

	// ===============================================================================================================
	// GOLD
	// ===============================================================================================================

	GameObject goldOre = GameObject("Gold ore");
	goldOre.addComponent<MeshRenderer>("Models/Product/GoldOre/GoldOre.obj");
	goldOre.addComponent<Product>(50, ProductType::GOLD_ORE);
	_products.push_back(goldOre);

	GameObject goldIngot = GameObject("Gold ingot");
	goldIngot.addComponent<MeshRenderer>("Models/Product/GoldIngot/GoldIngot.obj");
	goldIngot.addComponent<Product>(100, ProductType::GOLD_INGOT);
	_products.push_back(goldIngot);

	GameObject goldPlate = GameObject("Gold plate");
	goldPlate.addComponent<MeshRenderer>("Models/Product/GoldPlate/GoldPlate.obj");
	goldPlate.addComponent<Product>(125, ProductType::GOLD_PLATE);
	_products.push_back(goldPlate);

	GameObject cutGold = GameObject("Cut gold");
	cutGold.addComponent<MeshRenderer>("Models/Product/CutGold/CutGold.obj");
	cutGold.addComponent<Product>(80, ProductType::CUT_GOLD);
	_products.push_back(cutGold);

	GameObject goldWire = GameObject("Gold wire");
	goldWire.addComponent<MeshRenderer>("Models/Product/GoldWire/GoldWire.obj");
	goldWire.addComponent<Product>(225, ProductType::GOLD_WIRE);
	_products.push_back(goldWire);

	// ===============================================================================================================
	// ROSE GOLD
	// ===============================================================================================================

	GameObject roseGoldIngot = GameObject("Rose gold ingot");
	roseGoldIngot.addComponent<MeshRenderer>("Models/Product/RoseGoldIngot/RoseGoldIngot.obj");
	roseGoldIngot.addComponent<Product>(150, ProductType::ROSE_GOLD_INGOT);
	_products.push_back(roseGoldIngot);

	GameObject roseGoldPlate = GameObject("Rose gold plate");
	roseGoldPlate.addComponent<MeshRenderer>("Models/Product/RoseGoldPlate/RoseGoldPlate.obj");
	roseGoldPlate.addComponent<Product>(200, ProductType::ROSE_GOLD_PLATE);
	_products.push_back(roseGoldPlate);
}

GameObject* Prefabs::getPrefab(std::string name) {
	for (auto& prefab : _prefabs) {
		if (prefab.getName() == name) {
			return new GameObject(prefab);
		}
	}
	return new GameObject("Prefab not found");
}

GameObject* Prefabs::getProduct(ProductType type)
{
	for (auto& product : _products) {
		if (product.getComponent<Product>()->getType() == type) {
			return new GameObject(product);
		}
	}
	return new GameObject("Product not found");
}
