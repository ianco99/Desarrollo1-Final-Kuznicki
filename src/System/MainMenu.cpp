#include "MainMenu.h"

namespace kuznickiSystem
{
	MainMenu::MainMenu()
	{
		menuState = MenuState::Menu;

		InitButtons();
		InitBackground();
	}

	MainMenu::~MainMenu()
	{

	}

	void MainMenu::InitButtons()
	{
		for (int i = 0; i < buttonQuantity; i++)
		{
			buttons[i].body.width = static_cast<float>(GetScreenWidth()) / buttonXDivider;
			buttons[i].body.height = static_cast<float>(GetScreenHeight()) / buttonYDivider;
			buttons[i].body.x = static_cast<float>((GetScreenWidth() / 2)) - buttons[i].body.width / 2;
			buttons[i].body.y = static_cast<float>((GetScreenHeight() / 8) * (i * 1.5f) + GetScreenHeight() / 3) - buttons[i].body.height / 2;

			buttons[i].color = WHITE;
			buttons[i].fontSize = 24;
		}
		buttons[0].text = "PLAY (1P)";
		buttons[1].text = "INSTRUCTIONS";
		buttons[2].text = "CREDITS";
		buttons[3].text = "QUIT";

	}

	void MainMenu::InitBackground()
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

	void MainMenu::MenuLoop()
	{
		while (!WindowShouldClose() && !closeApp)
		{
			switch (menuState)
			{
			case kuznickiSystem::MenuState::Menu:
				CheckButtonColls(menuState);
				DrawMenu();
				break;
			case kuznickiSystem::MenuState::Game:

				break;
			case kuznickiSystem::MenuState::Instructions:
				instructionsMenu.CheckButtonColls(menuState);

				BeginDrawing();
				DrawBackground();
				instructionsMenu.DrawMenu();
				EndDrawing();
				break;
			case kuznickiSystem::MenuState::Credits:
				creditsMenu.CheckButtonColls(menuState);

				BeginDrawing();
				DrawBackground();
				creditsMenu.DrawMenu();
				EndDrawing();
				break;
			default:
				break;
			}


			if (IsKeyPressed(KEY_ESCAPE))
				closeApp = true;
		}
	}

	void MainMenu::CheckButtonColls(MenuState& menuState)
	{
		for (int i = 0; i < buttonQuantity; i++)
		{
			MainMenuButtons button = (MainMenuButtons)i;
			if (CheckCollisionPointRec(GetMousePosition(), buttons[i].body))
			{
				buttons[i].color = RED;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					switch (button)
					{
					case MainMenuButtons::Game:
						if (menuState != MenuState::Game)
						{
							menuState = MenuState::Game;
							runGame.Start(closeApp);
						}
						menuState = MenuState::Menu;

						break;
					case MainMenuButtons::Instructions:
						menuState = MenuState::Instructions;
						break;
					case MainMenuButtons::Credits:
						menuState = MenuState::Credits;
						break;
					case MainMenuButtons::Quit:
						closeApp = true;
						break;
					default:
						break;
					}

				}
			}
			else
			{
				buttons[i].color = WHITE;
			}
		}
	}

	void MainMenu::DrawMenu()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawBackground();

		for (int i = 0; i < buttonQuantity; i++)
		{
			DrawRectangleRec(buttons[i].body, buttons[i].color);
			DrawText(buttons[i].text, buttons[i].body.x + buttons[i].body.width / 2.0f - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).x / 2.0f,
					buttons[i].body.y + buttons[i].body.height / 2.0f - MeasureTextEx(GetFontDefault(), buttons[i].text, buttons[i].fontSize, 1).y / 2.0f, 
					buttons[i].fontSize, BLACK);
		}

		EndDrawing();

	}

	void MainMenu::DrawBackground()
	{
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
			Rectangle spriteDestination = { GetScreenWidth() / 2.0f,GetScreenHeight() / 2.0f, GetScreenWidth(), GetScreenHeight() };
			Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

			DrawTexturePro(imageToDraw.sprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);

			smallestLayer = imageToDraw.layer;
		}
	}
}