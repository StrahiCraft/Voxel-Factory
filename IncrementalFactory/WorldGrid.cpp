#include "WorldGrid.h"

bool WorldGrid::_gridOccupancy[32][32];
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
        if (!_gridOccupancy[(int)position.x][(int)position.y]) {
            return false;
        }
    }
    return true;
}

Machine* WorldGrid::getMachineAt(glm::vec2 position) {
    for (Machine* machine : _machines) {
        for (glm::vec2 machinePoint : machine->getOccupiedPoints()) {
            if (machinePoint == position) {
                return machine;
            }
        }
    }
    return nullptr;
}

void WorldGrid::placeMachine(Machine* machine) {
    _machines.push_back(machine);
    setGridOccupancyAt(machine->getOccupiedPoints(), true);
}

void WorldGrid::removeMachine(Machine* machine) {
    _machines.erase(std::remove(_machines.begin(), _machines.end(), machine), _machines.end());
    setGridOccupancyAt(machine->getOccupiedPoints(), false);
}

void WorldGrid::setGridOccupancyAt(std::vector<glm::vec2> positions, bool value) {
    for (auto position : positions) {
        _gridOccupancy[(int)position.x][(int)position.y] = value;
    }
}
