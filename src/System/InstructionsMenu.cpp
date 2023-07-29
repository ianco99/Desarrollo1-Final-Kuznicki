#include "InstructionsMenu.h"

namespace kuznickiSystem
{
	InstructionsMenu::InstructionsMenu()
	{
		instructionsBounds = { GetScreenWidth() / 2.0f - GetScreenWidth() / 2.4f, GetScreenHeight() / 12.0f, GetScreenWidth() / 1.2f, GetScreenHeight() / 1.35f };
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
		const char* myText0 = "In FEARLESS, your objective is to survive the longest.";
		const char* myText1 = "In FEARLESS, your objective is to survive the longest.";
		const char* myText2 = "In FEARLESS, your objective is to survive the longest.";
		const char* myText3 = "In FEARLESS, your objective is to survive the longest.";

		Vector2 textMeasure = MeasureTextEx(GetFontDefault(), myText0, 24, 1);
		Vector2 position = { instructionsBounds.x + instructionsBounds.width / 2.0f - textMeasure.x/2, instructionsBounds.y + instructionsBounds.height / 2.0f - textMeasure.y / 2 };
		DrawTextEx(GetFontDefault(), myText0, position, 24, 1, WHITE);

		DrawRectangleLinesEx(instructionsBounds, 2,GREEN);
		for (int i = 0; i < buttonQuantity; i++)
		{
			DrawRectangleRec(buttons[i].body, buttons[i].color);
			DrawText(buttons[i].text, buttons[i].body.x + buttons[i].body.width / 2 - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).x / 2, buttons[i].body.y + buttons[i].body.height / 2 - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).y / 2, buttons[i].fontSize, BLACK);
		}
	}
}