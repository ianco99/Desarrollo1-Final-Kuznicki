#pragma once
#include "Button.h"
#include "RunGame.h"
#include "BackgroundImage.h"
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
	const int backgroundQuantity = 6;

	class Menu
	{
	protected:

		Button buttons[buttonQuantity];
		BackgroundImage backgrounds[backgroundQuantity];

	public:
		Menu();
		~Menu();

		void InitButtons();
		void InitBackground();
		void MenuLoop();
		void CheckButtonColls();
		void DrawMenu();
	};

}