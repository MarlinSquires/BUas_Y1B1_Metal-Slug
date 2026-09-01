#include "precomp.h"
#include "game.h"



Sprite* spr = new Sprite(new Surface("assets/ball.png"), 1);


void Game::Init()
{
	




}


void Game::Tick( float dt)
{

	spr->Draw(Game::screen, 5, 5);


}