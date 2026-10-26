#include "precomp.h"
#include "actorSpawner.h"
#include "grid.h"
#include "enemyPrefab.h"
#include "prisonerPrefab.h"
#include "enemy.h"


void ActorSpawner::Spawn(Grid& grid)
{
	EnemyPrefab enemyPrefab;
	PrisonerPrefab prisonerPrefab;

	for (int y = 0; y < grid.height; y++)
	{
		for (int x = 0; x < grid.width; x++)
		{
			int i = x + y * grid.width;

			float2 pos = float2((float)x * grid.tileSize, (float)y * grid.tileSize);

			if (grid.tiles[i] == TileType::SpawnPrisoner)
			{
				float2 offset = { 0.0f, -15.0f };
				prisonerPrefab.Load(pos + offset);
			}

			else if (grid.tiles[i] == TileType::SpawnEnemy)
			{
				float2 offset = { 0.0f, -24.0f };
				enemyPrefab.Load(pos + offset, EnemyType::Basic);
			}
		}
	}
}