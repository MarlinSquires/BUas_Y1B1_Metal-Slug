#include "precomp.h"
#include "mainScene.h"

#include "gameObject.h"
#include "renderSystem.h"
#include "spriteRenderer.h"
#include "camera.h"
#include "spriteFactory.h"
#include "playerMove.h"
#include "gridSpawner.h"
#include "gridRenderer.h"



RenderSystem* rs = new RenderSystem();


void MainScene::LoadScene()
{

	// Ball object
	GameObject* go = new GameObject(float2(0.0f, 0.0f));
	go->AddComponent<SpriteRenderer>(1, 0);


	// Player object
	GameObject* player = new GameObject(float2(0.0f, 0.0f));
	player->AddComponent<SpriteRenderer>(2, 1);
	player->AddComponent<PlayerMove>();


	// Camera object
	GameObject* camGo = new GameObject(float2(0.0f, 0.0f));
	Camera& cam = camGo->AddComponent<Camera>();
	cam.SetTarget(player);

	
	// Grid object
	GridSpawner* gridSpawner = new GridSpawner("data/level1.tmj");
	gridSpawner->Init();
	Grid* grid = gridSpawner->GetGrid();
	delete gridSpawner;

	GameObject* gridGo = new GameObject(float2(0.0f, 0.0f));
	gridGo->AddComponent<GridRenderer>(grid);


}




