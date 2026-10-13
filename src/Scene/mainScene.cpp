#include "precomp.h"
#include "mainScene.h"

// Systems
#include "renderSystem.h"
#include "collisionSystem.h"

// Objects
#include "animationTypes.h"
#include "gridFactory.h"

// GOs & components
#include "gameObject.h"
#include "camera.h"
#include "rigidbody.h"
#include "fpsCounter.h"
#include "enemy.h"
#include "animator.h"

// Renderers
#include "spriteRenderer.h"
#include "gridRenderer.h"
#include "rectRenderer.h"
#include "textRenderer.h"
#include "lineRenderer.h"

// Colliders
#include "rectCollider.h"
#include "gridCollider.h"
#include "pixelCollider.h"

// Player
#include "playerController.h"
#include "playerMove.h"
#include "playerShoot.h"
#include "health.h"


// Prefabs
#include "enemyPrefab.h"


EnemyPrefab enemyPrefab;


// GameObjects add themselves to the scene objects[] array in their constructor
void MainScene::LoadScene()
{

	MyScene::LoadScene();


	// Rock object
	GameObject* rock = new GameObject(float2(400.0f, 228.0f));
	RectCollider& rockCol = rock->AddComponent<RectCollider>(CollisionLayerName::Solids, float2(80.0f, 40.0f));
	rock->AddComponent<RectRenderer>(&rockCol);


	// Player object
	GameObject* player = new GameObject(float2(200.0f, 50.0f)); 
	RectCollider& playerCol = player->AddComponent<RectCollider>(CollisionLayerName::Player, float2(20.0f, 38.0f));
	player->AddComponent<RectRenderer>(&playerCol);
	player->AddComponent<Rigidbody>();
	player->AddComponent<PlayerController>();


	// PlayerUpper child object
	GameObject* playerUpper = new GameObject(float2(0.0f, 0.0f), player);
	Animator& animUpper = playerUpper->AddComponent<Animator>(RenderLayerName::FGActors, AnimationSetName::PlayerUpper, 1);
	

	// PlayerLower child object
	GameObject* playerLower = new GameObject(float2(0.0f, 0.0f), player);
	Animator& animLower = playerLower->AddComponent<Animator>(RenderLayerName::BGActors, AnimationSetName::PlayerLower, 1);
	
	player->AddComponent<PlayerMove>(&animUpper, &animLower);
	player->AddComponent<PlayerShoot>();


	// Enemy objects
	enemyPrefab.Load(float2(100.0f, 0.0f), player);
	//enemyPrefab.Load(float2(200.0f, 0.0f), player);
	//enemyPrefab.Load(float2(300.0f, 0.0f), player);


	// Camera object
	GameObject* camGo = new GameObject(float2(0.0f, 0.0f));
	Camera& cam = camGo->AddComponent<Camera>();
	cam.SetTarget(player);

	// Grid object
	GameObject* gridGo = new GameObject(float2(0.0f, 0.0f));
	GridCollider& gridCol = gridGo->AddComponent<GridCollider>("data/level1_4.tmj");
	gridGo->AddComponent<GridRenderer>(&gridCol);

	// FPS Counter
	GameObject* textGo = new GameObject(float2(10.0f, 10.0f));
	textGo->AddComponent<TextRenderer>();
	textGo->AddComponent<FpsCounter>();
}




