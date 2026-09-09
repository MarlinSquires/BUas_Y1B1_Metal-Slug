#include "precomp.h"
#include "gameObject.h"
#include "jsonParser.h"
#include "gridSpawner.h"
#include "collider.h"



GridSpawner::~GridSpawner() {

	delete[] grid;
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
	grid = new uint[l];
	
	for (int i = 0; i < l; i++)
	{
		grid[i] = (layer["data"][i].get<uint>());
	}
}

int c = 0;

void GridSpawner::Init()
{
	gridObj = new GameObject(float2(0.0f, 0.0f), true, 1300);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			bool b = grid[x + y * width];

			if (b)
			{
				c++;

				gridObj->AddComponent<Collider>();

			}

		}
	}
	printf("value: %d\n", c);
}


