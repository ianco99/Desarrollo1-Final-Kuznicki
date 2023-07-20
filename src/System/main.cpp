#include <iostream>
#include "RunGame.h"

int main()
{
	kuznickiSystem::RunGame runGame = kuznickiSystem::RunGame();
	InitWindow(1024, 768, "MyFinal");
	runGame.Start();
	return 0;
}