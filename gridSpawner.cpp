#include "precomp.h"
#include "gameObject.h"
#include "jsonParser.h"
#include "grid.h"
#include "gridSpawner.h"
#include "collider.h"


#include "spriteRenderer.h" // delete later



GridSpawner::~GridSpawner() {

	delete[] gridData;
}


GridSpawner::GridSpawner(const char* address)
{
	data = JsonParser::Load(address);
	if (data == nullptr)
	{
		printf("didnt load");
		return;
	}
	json &layer = data["layers"][1];
	width = layer["width"].get<int>();
	height = layer["height"].get<int>();

	int l = width * height;
	gridData = new uint[l];
	
	for (int i = 0; i < l; i++)
	{
		gridData[i] = (layer["data"][i].get<uint>());
	}

	grid = new Grid(width, height, 8);

}


// Atm we have about 1200 tiles in the map
void GridSpawner::Init()
{
	

	for (int i = 0; i < width * height; i++)
	{
		grid->tiles[i] = gridData[i];
	}
}


