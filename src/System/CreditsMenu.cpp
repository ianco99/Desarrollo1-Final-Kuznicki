#include "CreditsMenu.h"

namespace kuznickiSystem
{
	CreditsMenu::CreditsMenu()
	{
		creditsBounds = { GetScreenWidth() / 2.0f - GetScreenWidth() / 2.4f, GetScreenHeight() / 12.0f, GetScreenWidth() / 1.2f, GetScreenHeight() / 1.35f };
		InitButtons();
		InitText();
	}

	CreditsMenu::~CreditsMenu()
	{

	}

	void CreditsMenu::InitButtons()
	{
		buttons[0].body.width = static_cast<float>(GetScreenWidth()) / 4;
		buttons[0].body.height = static_cast<float>(GetScreenHeight()) / 12;
		buttons[0].body.x = static_cast<float>((GetScreenWidth() / 2)) - buttons[0].body.width / 2;
		buttons[0].body.y = static_cast<float>((GetScreenHeight() / 8) * (3 * 1.5f) + GetScreenHeight() / 3) - buttons[0].body.height / 2;

		buttons[0].color = WHITE;
		buttons[0].fontSize = 24;

		buttons[0].text = "BACK";

		for (int i = 0; i < 10; i++)
		{
			linkButtons[i].color = SKYBLUE;
		}
	}

	void CreditsMenu::InitText()
	{
		const char* text0 = "GAME BACKGROUND art by:";
		linkButtons[0].text = "David Marah";
		linkButtons[0].link = "https://www.instagram.com/aethrall/?hl=es";

		const char* text1 = "MENU BACKGROUND art by:";
		linkButtons[1].text = "Szadi art";
		linkButtons[1].link = "https://szadiart.itch.io";

		const char* text2 = "GAME GROUND art by:";
		linkButtons[2].text = "Gikeota";
		linkButtons[2].link = "https://gikeota.itch.io";

		const char* text3 = "PLAYER art by:";
		linkButtons[3].text = "rvros";
		linkButtons[3].link = "https://rvros.itch.io";

		const char* text4 = "GUN art by:";
		linkButtons[4].text = "Mack";
		linkButtons[4].link = "https://bigmack.itch.io";

		texts[0] = text0;
		texts[1] = text1;
		texts[2] = text2;
		texts[3] = text3;
		texts[4] = text4;
	}

	void CreditsMenu::InitBackground()
	{

	}

	void CreditsMenu::MenuLoop()
	{
		//CheckButtonColls();
	}

	void CreditsMenu::CheckButtonColls(MenuState& menuState)
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

	void CreditsMenu::CheckButtonColls()
	{

	}

	void CreditsMenu::DrawMenu()
	{

		for (int i = 0; i < 5; i++)
		{
			Vector2 textMeasure = MeasureTextEx(GetFontDefault(), texts[i], 24, 1);
			Vector2 position = { creditsBounds.x + creditsBounds.width / 2.0f - textMeasure.x / 2, creditsBounds.y - textMeasure.y / 2 + (i + 1) * creditsBounds.height / 8.0f };
			DrawTextEx(GetFontDefault(), texts[i], position, 24, 1, WHITE);
			DrawTextEx(GetFontDefault(), linkButtons[i].text, { position.x + textMeasure.x + 48, position.y }, 24, 1, linkButtons->color);
		}

		DrawRectangleLinesEx(creditsBounds, 2.0f, GREEN);

		DrawTextures();

		for (int i = 0; i < buttonQuantity; i++)
		{
			DrawRectangleRec(buttons[i].body, buttons[i].color);
			DrawText(buttons[i].text, buttons[i].body.x + buttons[i].body.width / 2 - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).x / 2, buttons[i].body.y + buttons[i].body.height / 2 - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).y / 2, buttons[i].fontSize, BLACK);
		}
	}

	void CreditsMenu::DrawTextures()
	{

	}
}