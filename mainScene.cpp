#include "precomp.h"
#include "mainScene.h"

#include "gameObject.h"
#include "renderSystem.h"
#include "spriteRenderer.h"
#include "camera.h"
#include "spriteFactory.h"


GameObject* go = new GameObject(float2(0.0f, 0.0f));
GameObject* go2 = new GameObject(float2(0.5f, 0.5f));
GameObject* camGo = new GameObject(float2(0.0f, 0.0f));

RenderSystem* rs = new RenderSystem();


void MainScene::LoadScene()
{
	Camera& cam = camGo->AddComponent<Camera>();

	cam.SetTarget(go);

	//go->AddComponent<SpriteRenderer>(1, 0);
	go->AddComponent<SpriteRenderer>(1, 0);
	//go2->AddComponent<SpriteRenderer>(2, 1);

	LoadObject(camGo);
	LoadObject(go);
	//LoadObject(go2);
}




