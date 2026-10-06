#pragma once
#include "collider.h"
#include "grid.h"

// Gridcollider should instantiate the gridSpawner, gain ownership of Grid, and then pass Grid ref to GridRenderer


class GridCollider : public Collider
{
public:
	Grid& GetGrid() { return grid; }

	GridCollider(const char* address);

private:
	Grid grid = Grid(0, 0, 0);

};

