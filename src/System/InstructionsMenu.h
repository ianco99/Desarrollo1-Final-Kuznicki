#pragma once
#include "Menu.h"

namespace kuznickiSystem
{
	class InstructionsMenu : Menu
	{
	private:
		Rectangle instructionsBounds;
		Texture2D playerSprite;
		Texture2D enemySprite;
		Texture2D gunSprite;
		const char* texts[4];

	public:
		InstructionsMenu();
		~InstructionsMenu();

		void InitButtons() override;
		void InitText();
		void InitBackground() override;
		void MenuLoop() override;
		void CheckButtonColls(MenuState& gameState);
		void CheckButtonColls()override;
		void DrawMenu() override;
		void DrawTextures();
	};
}

