#pragma once
#include "Menu.h"

namespace kuznickiSystem
{
	static const int linkButtonsSize = 10;
	class CreditsMenu : Menu
	{
	private:
		Rectangle creditsBounds;
		Button linkButtons[linkButtonsSize];
		const char* texts[linkButtonsSize];
	public:
		CreditsMenu(Texture2D* buttonSprite);
		CreditsMenu();
		~CreditsMenu();



		void InitButtons(Texture2D* buttonSprite) override;
		void InitText();
		void InitBackground() override;
		void MenuLoop() override;
		void CheckButtonColls(MenuState& gameState);
		void DrawMenu() override;
		void DrawTextures();
	};
}