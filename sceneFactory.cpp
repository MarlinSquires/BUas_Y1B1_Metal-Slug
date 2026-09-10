#include "precomp.h"
#include "mainScene.h"
#include "sceneFactory.h"



void SceneFactory::Init()
{
	scenes[0] = new MainScene();
}

