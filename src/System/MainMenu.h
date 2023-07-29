#pragma once
#include "Menu.h"
#include "InstructionsMenu.h"

namespace kuznickiSystem
{
	class MainMenu : Menu
	{
	private:
		InstructionsMenu instructionsMenu;
		RunGame runGame;
		MenuState menuState;
		bool closeApp = false;

	public:
		MainMenu();
		~MainMenu();

		void InitButtons() override;
		void InitBackground() override;
		void MenuLoop() override;
		void CheckButtonColls() override;
		void DrawMenu() override;
		void DrawBackground();

	};
}
