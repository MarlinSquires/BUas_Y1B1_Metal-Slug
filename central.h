#pragma once

#include "game.h"

class GameObject;



class Central
{

public:
	// Main references
	static Tmpl8::Game* game;
	static Tmpl8::Surface* surface;

	// Camera
	static GameObject* camera;
	static const int screenWidth = 1500;
	static const int screenHeight = 1000;

	// Time
	static float dt;
	static float dts;

	static float elapsed;



};

