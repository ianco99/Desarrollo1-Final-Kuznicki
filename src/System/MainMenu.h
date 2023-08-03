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
		Texture2D baseButtonSprite;
		bool closeApp = false;

	public:
		MainMenu();
		~MainMenu();

		void InitButtons(Texture2D* buttonSprite) override;
		void InitBackground() override;
		void MenuLoop() override;
		void CheckButtonColls(MenuState& menuState) override;
		void DrawMenu() override;
		void DrawBackground();

	};
}
