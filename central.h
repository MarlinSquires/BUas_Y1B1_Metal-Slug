#pragma once

#include "game.h"

class GameObject;



class Central
{

public:
	// Main references
	static inline Tmpl8::Game* game = nullptr;
	static inline Tmpl8::Surface* surface = nullptr;

	// Camera
	static inline GameObject* camera = nullptr;
	static const int screenWidth = SCRWIDTH;
	static const int screenHeight = SCRHEIGHT;

	// Time
	static inline float dt = 0;
	static inline float dts = 0;

	static inline float elapsed = 0;



};

