#pragma once

#include "json.hpp"

using nlohmann::json;

struct Grid;

class GridSpawner
{
private:

	int width;
	int height;
	uint* gridData;

	json data;
	Grid* grid;

public:
	void Init();
	Grid* GetGrid() { return grid; };

	// Structors
	GridSpawner(const char* address);
	~GridSpawner();

};

