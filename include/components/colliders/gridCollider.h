#pragma once
#include "collider.h"
#include "grid.h"

// Gridcollider should instantiate the gridSpawner, gain ownership of Grid, and then pass Grid ref to GridRenderer


class GridCollider : public Collider
{
public:
	Grid* GetGrid() { return _grid; }

	GridCollider(Grid& g);

private:
	Grid* _grid = nullptr;

};

