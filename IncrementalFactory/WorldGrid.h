#pragma once
#include "Machine.h"

static class WorldGrid
{
private:
	static bool _gridOccupancy[32][32];
	static std::vector<Machine*> _machines;
public:
	static bool isGridFreeAt(int x, int y);
	static bool isGridFreeAt(glm::vec2 position);
	static bool isGridFreeAt(std::vector<glm::vec2> positions);

	static Machine* getMachineAt(glm::vec2 position);

	static void placeMachine(Machine* machine);
	static void removeMachine(Machine* machine);
private:
	static void setGridOccupancyAt(std::vector<glm::vec2> positions, bool value);
};

