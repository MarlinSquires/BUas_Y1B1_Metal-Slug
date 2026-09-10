#pragma once


struct Grid
{
	bool* tiles;
	int width;
	int height;
	int tileSize; // tile size in px


	Grid(int width, int height, int tileSize) : width(width), height(height), tileSize(tileSize) {
		tiles = new bool[width * height];

	}

};

