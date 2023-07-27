#include "Menu.h"
#include "Button.h"
#include <iostream>

namespace kuznickiSystem
{
	Menu::Menu()
	{
		menuState = MenuState::Menu;
		InitButtons();

		InitBackground();
	}

	Menu::~Menu()
	{

	}

	void Menu::InitButtons()
	{
		for (int i = 0; i < buttonQuantity; i++)
		{
			buttons[i].body.width = static_cast<float>(GetScreenWidth()) / 6;
			buttons[i].body.height = static_cast<float>(GetScreenHeight()) / 12;
			buttons[i].body.x = static_cast<float>((GetScreenWidth() / 2)) - buttons[i].body.width / 2;
			buttons[i].body.y = static_cast<float>((GetScreenHeight() / 8) * (i * 1.5f) + GetScreenHeight() / 3) - buttons[i].body.height / 2;

			buttons[i].color = WHITE;
			buttons[i].fontSize = 12;
		}
		buttons[0].text = "PLAY (1P)";
		buttons[1].text = "PLAY (2P)";
		buttons[2].text = "CREDITS";
		buttons[3].text = "QUIT";

	}

	void Menu::InitBackground()
	{
		for (int i = 0; i < backgroundQuantity; i++)
		{
			backgrounds[i].speedX = 200 * (i + 1);
			backgrounds[i].body = { 0,0,static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) };
			backgrounds[i].color = WHITE;
			backgrounds[i].layer = i;
		}
		backgrounds[0].sprite = LoadTexture("../rsc/menuBackground0.png");
		backgrounds[1].sprite = LoadTexture("../rsc/menuBackground1.png");
		backgrounds[2].sprite = LoadTexture("../rsc/menuBackground2.png");
		backgrounds[3].sprite = LoadTexture("../rsc/menuBackground3.png");
		backgrounds[4].sprite = LoadTexture("../rsc/menuBackground4.png");
		backgrounds[5].sprite = LoadTexture("../rsc/menuBackground5.png");
	}

	void Menu::MenuLoop()
	{
		while (!WindowShouldClose() && !closeApp)
		{
			CheckButtonColls();
			DrawMenu();

			if (IsKeyPressed(KEY_ESCAPE))
				closeApp = true;
		}
	}

	void Menu::CheckButtonColls()
	{
		for (int i = 0; i < buttonQuantity; i++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), buttons[i].body))
			{
				buttons[i].color = RED;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && menuState != MenuState::Game)
				{
					menuState = MenuState::Game;
					runGame.Start(closeApp);
				}
			}
			else
			{
				buttons[i].color = WHITE;
			}
		}
		menuState = MenuState::Menu;
	}

	void Menu::DrawMenu()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		int lastLayer = 1000;
		int smallestLayer = 0;
		int currentLayer = lastLayer;
		BackgroundImage imageToDraw;

		for (int i = 0; i < backgroundQuantity; i++)
		{
			currentLayer = lastLayer;
			for (int j = 0; j < backgroundQuantity; j++)
			{
				if (backgrounds[j].layer < currentLayer && backgrounds[j].layer > smallestLayer)
				{
					currentLayer = backgrounds[j].layer;
					imageToDraw = backgrounds[i];
				}
			}

			Rectangle spriteSource = { 0.0f,0.0f, imageToDraw.sprite.width, imageToDraw.sprite.height };
			Rectangle spriteDestination = { GetScreenWidth() / 2,GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight() };
			Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

			DrawTexturePro(imageToDraw.sprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);

			smallestLayer = imageToDraw.layer;
		}

		for (int i = 0; i < buttonQuantity; i++)
		{
			DrawRectangleRec(buttons[i].body, buttons[i].color);
			DrawText(buttons[i].text, buttons[i].body.x + 5, buttons[i].body.y + 5, buttons[i].fontSize, BLACK);
		}
		EndDrawing();
	}
}