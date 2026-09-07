#include "precomp.h"
#include "game.h"

#include "gameObject.h"
#include "renderSystem.h"
#include "spriteRenderer.h"
#include "camera.h"
#include "spriteFactory.h"

using namespace Tmpl8;

Sprite* spr = new Sprite(new Surface(SpriteFactory::sprites[0]), 1);
Sprite* spr2 = new Sprite(new Surface(SpriteFactory::sprites[1]), 36);

GameObject* go = new GameObject(float2(0.0f, 0.0f));
GameObject* go2 = new GameObject(float2(0.5f, 0.5f));
GameObject* camGo = new GameObject(float2(50.0f, 50.0f));


RenderSystem* rs = new RenderSystem();


void Game::Init()
{
	
	Camera& cam = camGo->AddComponent<Camera>();
	go->AddComponent<SpriteRenderer>(1,spr);
	go2->AddComponent<SpriteRenderer>(2, spr2);

	cam.SetTarget(go);

	go->Start();
	go2->Start();
	camGo->Start();

}

int counter = 0;
void Game::Tick( float /*dt*/)
{

	go->Tick();
	go2->Tick();
	camGo->Tick();
	rs->Tick();

}