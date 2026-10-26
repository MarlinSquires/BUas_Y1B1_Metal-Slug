#pragma once

class GameObject;

enum class EnemyType : uint8_t;


class EnemyPrefab
{
public:
	GameObject* Load(float2 spawnPos, EnemyType type);

};