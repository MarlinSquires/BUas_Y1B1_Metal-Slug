#pragma once



enum class TileType
{
	Empty,
	Solid,
	Passthrough,
	SlopeLeft,
	SlopeRight
};



struct Grid
{
	TileType* tiles;
	int width;
	int height;
	int tileSize; // tile size in px

	Grid(int width, int height, int tileSize);

};


