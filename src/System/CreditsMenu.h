#pragma once
#include "Menu.h"

namespace kuznickiSystem
{
	class CreditsMenu : Menu
	{
	private:
		Rectangle creditsBounds;
		Button linkButtons[10];
		const char* texts[10];
	public:
		CreditsMenu();
		~CreditsMenu();



		void InitButtons() override;
		void InitText();
		void InitBackground() override;
		void MenuLoop() override;
		void CheckButtonColls(MenuState& gameState);
		void DrawMenu() override;
		void DrawTextures();
	};
}