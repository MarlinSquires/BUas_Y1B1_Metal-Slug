#include "precomp.h"
#include "mainScene.h"

// Systems
#include "renderSystem.h"
#include "collisionSystem.h"

// Objects
#include "spriteFactory.h"
#include "gridFactory.h"

// GOs & components
#include "gameObject.h"
#include "playerMove.h"
#include "camera.h"
#include "rigidbody.h"
#include "fpsCounter.h"

// Renderers
#include "spriteRenderer.h"
#include "gridRenderer.h"
#include "rectRenderer.h"
#include "textRenderer.h"

// Colliders
#include "rectCollider.h"
#include "gridCollider.h"
#include "pixelCollider.h"


RenderSystem rs = RenderSystem();




// GameObjects add themselves to the scene objects[] array in their constructor
void MainScene::LoadScene()
{
	// Ball object
	GameObject* ball = new GameObject(float2(0.0f, 0.0f));
	SpriteRenderer& ballRend = ball->AddComponent<SpriteRenderer>(RenderLayerType::BackgroundSprites, SpriteType::Ball);
	RectCollider& ballCol = ball->AddComponent<RectCollider>(CollisionLayerType::Player, ballRend.GetSprite());
	ball->AddComponent<RectRenderer>(&ballCol);

	// Ball2 object
	GameObject* ball2 = new GameObject(float2(60.0f, 0.5f));
	SpriteRenderer& ball2Rend = ball2->AddComponent<SpriteRenderer>(RenderLayerType::Actors, SpriteType::Ball);
	RectCollider& ball2Col = ball2->AddComponent<RectCollider>(CollisionLayerType::Player, ball2Rend.GetSprite());
	ball->AddComponent<RectRenderer>(&ball2Col);

	// Player object
	GameObject* player = new GameObject(float2(100.0f, 50.0f)); 
	SpriteRenderer& playerRend = player->AddComponent<SpriteRenderer>(RenderLayerType::Actors, SpriteType::Player);
	RectCollider& playerCol = player->AddComponent<RectCollider>(CollisionLayerType::Player, playerRend.GetSprite());
	player->AddComponent<RectRenderer>(&playerCol);
	player->AddComponent<PlayerMove>();
	player->AddComponent<Rigidbody>();


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




