#pragma once

struct Grid;

// Reads a grid object to spawn enemies and POWs in their correct positions

class ActorSpawner
{
public:
	void Spawn(Grid& grid);
};