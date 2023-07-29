#pragma once
#include "Menu.h"

namespace kuznickiSystem
{
	class InstructionsMenu : Menu
	{
	private:

	public:
		InstructionsMenu();
		~InstructionsMenu();

		void InitButtons() override;
		void InitBackground() override;
		void MenuLoop() override;
		void CheckButtonColls(MenuState& gameState);
		void CheckButtonColls()override;
		void DrawMenu() override;
	};
}

