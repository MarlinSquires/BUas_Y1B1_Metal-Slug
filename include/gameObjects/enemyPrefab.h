#pragma once

class GameObject;




class EnemyPrefab
{
public:
	GameObject* Load(float2 spawnPos, GameObject* player);

};