#pragma once
#include "Button.h"
namespace kuznickiSystem
{
	const int buttonQuantity = 4;

	class Menu
	{
	private:
		Button buttons[buttonQuantity];

	public:
		Menu();
		~Menu();

		void InitButtons();
		void MenuLoop();
		void CheckButtonColls();
		void DrawMenu();
	};
}