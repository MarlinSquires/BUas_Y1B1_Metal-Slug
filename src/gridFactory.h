#pragma once

struct Grid;

class GridFactory
{
public:

	Grid BuildGrid(const char* address);

};

