#pragma once
#include "Component.h"
#include <vector>
class Machine :
    public Component
{
private:
    float _delay;
    glm::vec2 _machineCenterPosition;
    std::vector<glm::vec2> _occupiedPoints;
    glm::vec2 _inputPositions;
    glm::vec2 _outputPositions;
public:
    std::vector<glm::vec2> getOccupiedPoints();
};

