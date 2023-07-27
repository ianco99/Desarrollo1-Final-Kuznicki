#include "Menu.h"
#include "Button.h"
#include <iostream>

namespace kuznickiSystem
{
	Menu::Menu()
	{
		menuState = MenuState::Menu;
		InitButtons();
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
		
		for (int i = 0; i < buttonQuantity; i++)
		{
			DrawRectangleRec(buttons[i].body, buttons[i].color);
			DrawText(buttons[i].text, buttons[i].body.x + 5, buttons[i].body.y + 5, buttons[i].fontSize, BLACK);
		}
		EndDrawing();
	}
}