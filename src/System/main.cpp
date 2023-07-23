#include <iostream>
#include "Menu.h"

bool wantsToQuit = false;

int main()
{
	InitWindow(1024, 768, "MyFinal");
	kuznickiSystem::Menu menu = kuznickiSystem::Menu();
	menu.MenuLoop();
	CloseWindow();
	return 0;
}