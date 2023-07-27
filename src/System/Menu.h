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
		Instructions,
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

		virtual void InitButtons() = 0;
		virtual void InitBackground() = 0;
		virtual void MenuLoop() = 0;
		virtual void CheckButtonColls() = 0;
		virtual void DrawMenu() = 0;
	};

}