#include "Menu.h"
#include "Button.h"
namespace kuznickiSystem
{

	Menu::Menu()
	{
		InitButtons();
	}

	Menu::~Menu()
	{

	}

	void Menu::InitButtons()
	{
		//buttons[0]

	}

	void Menu::MenuLoop()
	{
		while (!WindowShouldClose())
		{
			CheckButtonColls();
			DrawMenu();
		}
	}

	void Menu::DrawMenu()
	{
		for (int i = 0; i < buttonQuantity; i++)
		{
			//DrawRectangle();
		}
	}
}