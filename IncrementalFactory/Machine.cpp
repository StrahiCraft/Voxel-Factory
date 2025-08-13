#include "Machine.h"

std::vector<glm::vec2> Machine::getOccupiedPoints()
{
    std::vector<glm::vec2> occupiedPoints;
    occupiedPoints.push_back(_machineCenterPosition);

    for (auto position : _occupiedPoints) {
        occupiedPoints.push_back(position + _machineCenterPosition);
    }

    return occupiedPoints;
}
