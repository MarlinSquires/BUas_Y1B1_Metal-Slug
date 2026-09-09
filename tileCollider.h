#pragma once
#include "component.h"



class TileCollider : public Component
{
public:

	void InitTiles();
	void Start() override;
	void Tick() override;

private:

	int width;
	int height;
	int tileSize;

	/*Collider tiles[];*/

};

