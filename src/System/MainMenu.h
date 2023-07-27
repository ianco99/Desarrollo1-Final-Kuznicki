#pragma once
#include "Menu.h"
#include "InstructionsMenu.h"

namespace kuznickiSystem
{
	class MainMenu : Menu
	{
	private:

		RunGame runGame;
		MenuState menuState;
		bool closeApp = false;

	public:
		MainMenu();
		~MainMenu();

		void InitButtons();
		void InitBackground();
		void MenuLoop();
		void CheckButtonColls();
		void DrawMenu();

	};
}
