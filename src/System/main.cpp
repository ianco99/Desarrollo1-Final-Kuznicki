#include "MainMenu.h"

int main()
{
	InitWindow(1024, 768, "MyFinal");
	SetExitKey(NULL);
	kuznickiSystem::MainMenu menu = kuznickiSystem::MainMenu();
	menu.MenuLoop();
	CloseWindow();
	return 0;
}