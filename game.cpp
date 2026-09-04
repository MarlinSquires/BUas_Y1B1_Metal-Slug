#include "precomp.h"
#include "game.h"
#include <iostream>
#include <vector>


int PosToIndex(int x, int y)
{
	int r = x + y * SCRWIDTH;
	
	if (r <= SCRWIDTH * SCRHEIGHT)
	{
		return r;
	}

	else return SCRWIDTH * SCRHEIGHT;
}


struct Particle
{
	float2 pos;
	bool blocked = false;
	float2 moveDir = float2(0.0f, 1.0f);

	int colour = 0xFF0000;

	enum Type
	{
		Red, Green, Blue
	} type;


	void Move()
	{

		switch (type)
		{
			case Red:
				if (!blocked)
				{
					pos += moveDir;
				}
				break;

			case Green:
				if (!blocked)
				{
					pos += moveDir;
				}
				else
				{
					moveDir = (0, -1);
				}
				break;

			case Blue:
				if (!blocked)
				{
					pos += moveDir;
				}
				else
				{
					moveDir = (-1, 0);
				}
				break;
		}
		
	}

	void CheckBlocked(Surface* scr)
	{
		if (blocked) return;
		
		bool h = pos.y + 1 == SCRHEIGHT;
		bool b = scr->pixels[PosToIndex(pos.x, pos.y + 1)] != 0x000000;
		if (h || b)
		{
			blocked = true;
		}


	}

	void Draw(Surface* scr)
	{
		scr->Plot(pos.x, pos.y, colour);
	}



	Particle(float2 spawnPos) : pos(spawnPos)
	{
		type = static_cast<Type>(rand() % 3);

		switch (type)
		{
			case Red:
				colour = 0xFF0000;
				break;
			case Green:
				colour = 0x00FF00;
				break;
			case Blue:
				colour = 0x0000FF;
				break;
		}
	};

};



vector<Particle> particles;



void Game::Init()
{
	particles.reserve(100000);
}


int spawnRate = 3;
int spawnCount = 500;



void Game::Tick( float /* deltaTime */ )
{
	screen->Clear(0x000000);
	
	// Spawn particles
	for (int i = 0; i < spawnRate; i++)
	{
		particles.push_back(Particle(float2(rand() % SCRWIDTH, 0)));
	}

	// animate particles
	for (auto& p : particles)
	{
		p.CheckBlocked(screen);
		p.Move();
		p.Draw(screen);
	}

}


