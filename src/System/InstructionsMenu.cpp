#include "InstructionsMenu.h"

namespace kuznickiSystem
{
	InstructionsMenu::InstructionsMenu()
	{
		instructionsBounds = { GetScreenWidth() / 2.0f - GetScreenWidth() / 2.4f, GetScreenHeight() / 12.0f, GetScreenWidth() / 1.2f, GetScreenHeight() / 1.35f };
		InitButtons();
		InitText();

		playerSprite = LoadTexture("../rsc/adventurer-idle-00.png");

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

	void InstructionsMenu::InitText()
	{
		const char* myText0 = "In FEARLESS, your objective is to survive the longest.";
		const char* myText1 = "You will be equiped with a WEAPON which can only fire one bullet at a time.";
		const char* myText2 = "SHOOT or DODGE enemies to survive.";
		const char* myText3 = "Your character can recieve up to three hits. After that, you lose.";

		texts[0] = myText0;
		texts[1] = myText1;
		texts[2] = myText2;
		texts[3] = myText3;
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

		for (int i = 0; i < 4; i++)
		{
			Vector2 textMeasure = MeasureTextEx(GetFontDefault(), texts[i], 24, 1);
			Vector2 position = { instructionsBounds.x + instructionsBounds.width / 2.0f - textMeasure.x / 2, instructionsBounds.y - textMeasure.y / 2 + (i+1) * instructionsBounds.height/8.0f};
			DrawTextEx(GetFontDefault(), texts[i], position, 24, 1, WHITE);
		}

		DrawTextures();

		DrawRectangleLinesEx(instructionsBounds, 2,GREEN);
		for (int i = 0; i < buttonQuantity; i++)
		{
			DrawRectangleRec(buttons[i].body, buttons[i].color);
			DrawText(buttons[i].text, buttons[i].body.x + buttons[i].body.width / 2 - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).x / 2, buttons[i].body.y + buttons[i].body.height / 2 - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).y / 2, buttons[i].fontSize, BLACK);
		}
	}

	void InstructionsMenu::DrawTextures()
	{
		Rectangle spriteSource = { 0.0f,0.0f, playerSprite.width, playerSprite.height };
		Rectangle spriteDestination = { instructionsBounds.x + instructionsBounds.width / 8.0f,(instructionsBounds.height - instructionsBounds.height/5.0f), playerSprite.width * 4.75f, playerSprite.height * 4.375f};
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		//DrawRectanglePro(bullets[i].GetRadius(), spriteOrigin, bullets[i].GetAngle(), bullets[i].GetColor());
		DrawTexturePro(playerSprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
	}
}