#pragma once
#include "Button.h"
#include "RunGame.h"
namespace kuznickiSystem
{
	enum class MenuState
	{
		Menu,
		Game,
		Configurations,
		Credits,
		Quit
	};
	const int buttonQuantity = 4;

	class Menu
	{
	private:
		RunGame runGame;
		Button buttons[buttonQuantity];
		MenuState menuState;

		bool closeApp = false;

	public:
		Menu();
		~Menu();

		void InitButtons();
		void MenuLoop();
		void CheckButtonColls();
		void DrawMenu();
	};
}