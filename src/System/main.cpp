#include <iostream>
#include "Menu.h"

int main()
{
	InitWindow(1024, 768, "MyFinal");
	SetExitKey(NULL);
	kuznickiSystem::Menu menu = kuznickiSystem::Menu();
	menu.MenuLoop();
	CloseWindow();
	return 0;
}