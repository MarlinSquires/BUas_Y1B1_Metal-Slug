#pragma once



enum class TileType : uint8_t
{
	Empty,
	Solid,
	Passthrough,
	SlopeLeft,
	SlopeRight, 
	COUNT
};



struct Grid
{
	TileType* tiles;
	int width;
	int height;
	int tileSize; // tile size in px

	Grid(int width, int height, int tileSize);

};


