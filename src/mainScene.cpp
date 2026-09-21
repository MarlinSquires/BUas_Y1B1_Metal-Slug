#include "precomp.h"
#include "mainScene.h"

// Systems
#include "renderSystem.h"
#include "collisionSystem.h"

// Objects
#include "spriteFactory.h"
#include "gridSpawner.h"

// GOs & components
#include "gameObject.h"
#include "playerMove.h"
#include "camera.h"
#include "rigidbody.h"

// Renderers
#include "spriteRenderer.h"
#include "gridRenderer.h"
#include "rectRenderer.h"

// Colliders
#include "rectCollider.h"
#include "gridCollider.h"
#include "pixelCollider.h"


RenderSystem rs = RenderSystem();


void MainScene::LoadScene()
{
	// Ball object
	GameObject* ball = new GameObject(float2(0.0f, 0.0f));
	SpriteRenderer& ballRend = ball->AddComponent<SpriteRenderer>(RenderLayerType::BackgroundSprites, 0);
	RectCollider& ballCol = ball->AddComponent<RectCollider>(CollisionLayerType::Player, ballRend.GetSprite());
	ball->AddComponent<RectRenderer>(&ballCol);


	// Player object
	GameObject* player = new GameObject(float2(50.0f, 0.0f)); 
	SpriteRenderer& playerRend = player->AddComponent<SpriteRenderer>(RenderLayerType::Actors, 1);
	RectCollider& playerCol = player->AddComponent<RectCollider>(CollisionLayerType::Player, playerRend.GetSprite());
	player->AddComponent<RectRenderer>(&playerCol);
	player->AddComponent<PlayerMove>();
	player->AddComponent<Rigidbody>();


	// Camera object
	GameObject* camGo = new GameObject(float2(0.0f, 0.0f));
	Camera& cam = camGo->AddComponent<Camera>();
	cam.SetTarget(player);

	
	// Grid object
	GridSpawner* gridSpawner = new GridSpawner("data/level1-1.tmj");
	gridSpawner->Init();
	Grid* grid = gridSpawner->GetGrid();

	GameObject* gridGo = new GameObject(float2(0.0f, 0.0f));
	GridCollider& gridCol = gridGo->AddComponent<GridCollider>(grid);
	gridGo->AddComponent<GridRenderer>(&gridCol);


}




