#pragma once
#include "Menu.h"
#include "InstructionsMenu.h"
#include "CreditsMenu.h"

namespace kuznickiSystem
{
	enum class MainMenuButtons
	{
		Game,
		Instructions,
		Credits,
		Quit
	};

	class MainMenu : Menu
	{
	private:
		CreditsMenu creditsMenu;
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
		void CheckButtonColls(MenuState& menuState) override;
		void DrawMenu() override;
		void DrawBackground();

	};
}
