#include "precomp.h"
#include "game.h"
#include <iostream>






void Game::Init()
{
	// Bitwise manipulation practice
	/*Surface s("assets/nc2tiles.png");

	uint* ptr = s.pixels;

	int length = s.width * s.height;


	for (int i = 0; i < length; i++)
	{
		ptr[i] &= 0xFF0000;
	}

	s.CopyTo(screen, 0, 0);*/


	struct Test { char a, c; int b; };

	int a = sizeof(Test);

	std::cout << a;


}




void Game::Tick( float /* deltaTime */ )
{

	

}