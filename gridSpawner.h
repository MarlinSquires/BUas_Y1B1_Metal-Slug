#pragma once

#include "json.hpp"

using nlohmann::json;

class GridSpawner
{
private:

	int width;
	int height;
	uint* grid;

	char tileSize = 8;

	json data;
	GameObject* gridObj;

	~GridSpawner();

public:
	void Init();
	GridSpawner(const char* address);

};

