#include "precomp.h"
#include "grid.h"



Grid::Grid(int width, int height, int tileSize) : 
	width(width), height(height), tileSize(tileSize) 
{
	tiles = new bool[width * height];
}

