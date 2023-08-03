#include "InstructionsMenu.h"

namespace kuznickiSystem
{
	InstructionsMenu::InstructionsMenu(Texture2D* buttonSprite)
	{
		instructionsBounds = { GetScreenWidth() / 2.0f - GetScreenWidth() / 2.4f, GetScreenHeight() / 12.0f, GetScreenWidth() / 1.2f, GetScreenHeight() / 1.35f };
		InitButtons(buttonSprite);
		InitText();

		playerSprite = LoadTexture("../rsc/adventurer-idle-00.png");
		gunSprite = LoadTexture("../rsc/gun.png");
		enemySprite = LoadTexture("../rsc/enemy.png");
	}

	InstructionsMenu::InstructionsMenu()
	{

	}

	InstructionsMenu::~InstructionsMenu()
	{

	}

	void InstructionsMenu::InitButtons(Texture2D* buttonSprite)
	{
		buttons[0].body.width = static_cast<float>(GetScreenWidth()) / buttonXDivider;
		buttons[0].body.height = static_cast<float>(GetScreenHeight()) / buttonYDivider;
		buttons[0].body.x = static_cast<float>((GetScreenWidth() / 2)) - buttons[0].body.width / 2;
		buttons[0].body.y = static_cast<float>((GetScreenHeight() - (GetScreenHeight() / 8) * 2));

		buttons[0].color = WHITE;
		buttons[0].fontSize = 24;

		buttons[0].text = "BACK";

		buttons[0].sprite = buttonSprite;
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

	void InstructionsMenu::DrawMenu()
	{

		for (int i = 0; i < 4; i++)
		{
			Vector2 textMeasure = MeasureTextEx(GetFontDefault(), texts[i], 24, 1);
			Vector2 position = { instructionsBounds.x + instructionsBounds.width / 2.0f - textMeasure.x / 2, instructionsBounds.y - textMeasure.y / 2 + (i + 1) * instructionsBounds.height / 8.0f };
			DrawTextEx(GetFontDefault(), texts[i], position, 24, 1, WHITE);
		}

		DrawTextures();

		DrawText(buttons[0].text, buttons[0].body.x + buttons[0].body.width / 2 - MeasureTextEx(GetFontDefault(), buttons[0].text, buttons[0].fontSize, 1).x / 2, buttons[0].body.y + buttons[0].body.height / 2 - MeasureTextEx(GetFontDefault(), buttons[0].text, buttons[0].fontSize, 1).y / 2, buttons[0].fontSize, BLACK);

	}

	void InstructionsMenu::DrawTextures()
	{
		Rectangle playerSource = { 0.0f,0.0f, playerSprite.width, playerSprite.height };
		Rectangle playerDestination = { instructionsBounds.x + instructionsBounds.width / 8.0f,(instructionsBounds.height - instructionsBounds.height / 5.0f), playerSprite.width * 4.75f, playerSprite.height * 4.375f };
		Vector2 playerOrigin = { playerDestination.width / 2.0f, playerDestination.height / 2.0f };

		DrawTexturePro(playerSprite, playerSource, playerDestination, playerOrigin, 0.0f, WHITE);

		Rectangle gunSource = { 0.0f,0.0f, gunSprite.width, gunSprite.height };
		Rectangle gunDestination = { instructionsBounds.x + instructionsBounds.width / 2.0f, (instructionsBounds.height - instructionsBounds.height / 5.0f), gunSprite.width * 9.5f, gunSprite.height * 8.750f };
		Vector2 gunOrigin = { gunDestination.width / 2.0f, gunDestination.height / 2.0f };

		DrawTexturePro(gunSprite, gunSource, gunDestination, gunOrigin, 0.0f, WHITE);

		Rectangle enemySource = { 0.0f,0.0f, enemySprite.width, enemySprite.height };
		Rectangle enemyDestination = { instructionsBounds.x + instructionsBounds.width - instructionsBounds.width / 8.0f, (instructionsBounds.height - instructionsBounds.height / 5.0f), gunSprite.width * 8.0f, gunSprite.height * 8.750f };
		Vector2 enemyOrigin = { gunDestination.width / 2.0f, gunDestination.height / 2.0f };

		DrawTexturePro(enemySprite, enemySource, enemyDestination, enemyOrigin, 0.0f, WHITE);

		Rectangle buttonSource = { 0.0f, 0.0f, buttons[0].sprite->width, buttons[0].sprite->height };
		Rectangle buttonDestination = { buttons->body.x + buttons[0].body.width /2, buttons->body.y + buttons[0].body.height /2, buttons[0].body.width , buttons[0].body.height};
		Vector2 buttonOrigin = { buttonDestination.width / 2.0f, buttonDestination.height / 2.0f };

		DrawTexturePro(*buttons[0].sprite, buttonSource, buttonDestination, buttonOrigin, 0.0f, buttons[0].color);
	}
}