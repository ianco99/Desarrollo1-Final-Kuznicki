#include "InstructionsMenu.h"

namespace kuznickiSystem
{
	InstructionsMenu::InstructionsMenu()
	{
		InitButtons();
	}

	InstructionsMenu::~InstructionsMenu()
	{

	}

	void InstructionsMenu::InitButtons()
	{
		buttons[0].body.width = static_cast<float>(GetScreenWidth()) / 4;
		buttons[0].body.height = static_cast<float>(GetScreenHeight()) / 12;
		buttons[0].body.x = static_cast<float>((GetScreenWidth() / 2)) - buttons[0].body.width / 2;
		buttons[0].body.y = static_cast<float>((GetScreenHeight() / 8) * (3 * 1.5f) + GetScreenHeight() / 3) - buttons[0].body.height / 2;

		buttons[0].color = WHITE;
		buttons[0].fontSize = 24;

		buttons[0].text = "BACK";
	}

	void InstructionsMenu::InitBackground()
	{

	}

	void InstructionsMenu::MenuLoop()
	{
		//CheckButtonColls();
	}

	void InstructionsMenu::CheckButtonColls(MenuState& menuState)
	{
		for (int i = 0; i < buttonQuantity; i++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), buttons[i].body))
			{
				buttons[i].color = RED;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					menuState = MenuState::Menu;
				}
			}
			else
			{
				buttons[i].color = WHITE;
			}
		}
	}

	void InstructionsMenu::CheckButtonColls()
	{

	}

	void InstructionsMenu::DrawMenu()
	{
		for (int i = 0; i < buttonQuantity; i++)
		{
			DrawRectangleRec(buttons[i].body, buttons[i].color);
			DrawText(buttons[i].text, buttons[i].body.x + buttons[i].body.width / 2 - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).x / 2, buttons[i].body.y + buttons[i].body.height / 2 - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).y / 2, buttons[i].fontSize, BLACK);
		}
	}
}