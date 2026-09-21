#pragma once
#include "collider.h"

struct Grid;

class GridCollider : public Collider
{
public:
	Grid* GetGrid() { return grid; }

	GridCollider(Grid* grid);

private:
	Grid* grid;

};

