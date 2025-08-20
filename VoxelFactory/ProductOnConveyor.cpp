#include "ProductOnConveyor.h"
#include "GameObject.h"

ProductOnConveyor::ProductOnConveyor(Machine* conveyor) {
	_conveyor = conveyor;
	_currentType = ProductType::NOTHING;
}

void ProductOnConveyor::update() {
	_conveyor = getOwner()->getParent()->getComponent<Machine>();

	if (_conveyor->getProductType() != _currentType) {
		_currentType = _conveyor->getProductType();

		getOwner()->getComponent<MeshRenderer>()->setMesh(Prefabs::getProduct(_currentType)->getComponent<MeshRenderer>()->getMeshes());
	}
}

Component* ProductOnConveyor::copy() {
	return new ProductOnConveyor(_conveyor);
}