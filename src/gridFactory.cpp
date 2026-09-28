#include "precomp.h"
#include "gameObject.h"
#include "jsonParser.h"
#include "grid.h"
#include "gridFactory.h"
#include "collider.h"



Grid GridFactory::BuildGrid(const char* address)
{
	// Load json file
	json data = JsonParser::Load(address);

	//const bool didLoad = data == nullptr
	FATALERROR_IF(data.is_null(), "JSON data failed to load!!!");

	// Access json data
	json& layer = data["layers"][1];
	int width = layer["width"].get<int>();
	int height = layer["height"].get<int>();

	int l = width * height;
	uint* gridData = new uint[l];

	for (int i = 0; i < l; i++)
	{
		gridData[i] = (layer["data"][i].get<uint>());
	}

	// Instantiate grid object and pass data
	Grid grid = Grid(width, height, 8);

	for (int i = 0; i < width * height; i++)
	{
		grid.tiles[i] = static_cast<char>(gridData[i]); 
	}

	delete[] gridData; // Clean up memory

	return grid;
}


