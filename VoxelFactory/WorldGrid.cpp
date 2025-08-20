#include "WorldGrid.h"

bool WorldGrid::_gridOccupancy[32 * 32];
std::vector<Machine*> WorldGrid::_machines;

bool WorldGrid::isGridFreeAt(int x, int y) {
    return isGridFreeAt(glm::vec2(x, y));
}

bool WorldGrid::isGridFreeAt(glm::vec2 position) {
    std::vector<glm::vec2> positions;
    positions.push_back(position);
    return isGridFreeAt(positions);
}

bool WorldGrid::isGridFreeAt(std::vector<glm::vec2> positions) {
    for (auto& position : positions) {
        if (_gridOccupancy[(int)position.x + 32 * (int)position.y]) {
            return false;
        }
    }
    return true;
}

Machine* WorldGrid::getMachineAt(glm::vec2 position) {
    for (Machine* machine : _machines) {
        glm::vec3 machinePosition = machine->getOwner()->getComponent<Transform>()->_position;
        if (glm::vec2((int)machinePosition.x, (int)machinePosition.z) == position) {
            return machine;
        }
    }
    return nullptr;
}

void WorldGrid::placeMachine(GameObject* machineObject) {
    Machine* machine = machineObject->getComponent<Machine>();
    _machines.push_back(machine);
    glm::vec3 machinePosition = machine->getOwner()->getComponent<Transform>()->_position;
    setGridOccupancyAt(glm::vec2((int)machinePosition.x, (int)machinePosition.z), true);

    World::addObject(machineObject);
}

void WorldGrid::removeMachine(Machine* machine) {
    glm::vec3 machinePosition = machine->getOwner()->getComponent<Transform>()->_position;
    _machines.erase(std::remove(_machines.begin(), _machines.end(), machine), _machines.end());
    setGridOccupancyAt(glm::vec2((int)machinePosition.x, (int)machinePosition.z), false);

    World::removeObject(machine->getOwner());
}

void WorldGrid::debugPrint() {

}

void WorldGrid::setGridOccupancyAt(glm::vec2 position, bool value) {
    _gridOccupancy[(int)position.x + 32 * (int)position.y] = value;
}


