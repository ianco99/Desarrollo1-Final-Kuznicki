#include <iostream>

#include "RunGame.h"
#include "raylib.h"
#include "raymath.h"
#include "Player.h"

using namespace kuznickiGameObjects;
namespace kuznickiSystem
{
	void SetupEnemies(Enemy enemies[], Texture2D* enemySprite);

	RunGame::RunGame()
	{
		pauseBox = { GetScreenWidth() / 2.0f - GetScreenWidth() / 4.0f, GetScreenHeight() / 4.0f, GetScreenWidth() / 2.0f, GetScreenHeight() / 2.5f };
		LoadButtons();
		LoadTextures();

		score = 0;
	}

	RunGame::~RunGame()
	{
		UnloadTexture(ground);
		UnloadTexture(background0);
		UnloadTexture(background1);
		UnloadTexture(background2);
		UnloadTexture(background3);

		UnloadTexture(enemySprite);
	}

	void RunGame::LoadTextures()
	{
		ground = LoadTexture("../rsc/ground.png");
		background0 = LoadTexture("../rsc/parallax-demon-woods-bg.png");
		background1 = LoadTexture("../rsc/parallax-demon-woods-far-trees.png");
		background2 = LoadTexture("../rsc/parallax-demon-woods-mid-trees.png");
		background3 = LoadTexture("../rsc/parallax-demon-woods-close-trees.png");

		enemySprite = LoadTexture("../rsc/enemy.png");
	}

	void RunGame::LoadButtons()
	{
		Vector2 pauseButtonDividers = { 3.0f, 6.0f };
		for (int i = 0; i < 2; i++)
		{
			pauseButtons[i].body.width = static_cast<float>(pauseBox.width) / pauseButtonDividers.x;
			pauseButtons[i].body.height = static_cast<float>(pauseBox.height) / pauseButtonDividers.y;
			pauseButtons[i].body.x = static_cast<float>((pauseBox.x + pauseBox.width / 2)) - pauseButtons[i].body.width / 2;
			pauseButtons[i].body.y = static_cast<float>((pauseBox.y + pauseBox.height / 3.0f) + (i * pauseBox.height / 3.0f));

			pauseButtons[i].color = WHITE;
			pauseButtons[i].fontSize = 24;
		}

		deathButton = pauseButtons[0];
		deathButton.text = "GO TO MENU";

		pauseButtons[0].text = "CONTINUE";
		pauseButtons[1].text = "GO TO MENU";
	}

	void RunGame::Start(bool& closeApp)
	{
		Init();

		SetupEnemies(enemies, &enemySprite);

		while (inGame)
		{
			CheckGameStateConditions();

			if (gameState == GameState::Playing)
			{
				ManageEnemies();

				TakeInput();

				Update();


				DrawFrame();
			}
			if (gameState == GameState::Pause)
			{
				Color pauseBoxColor = { 255,100,100,255 };

				CheckButtonColls();

				BeginDrawing();

				CheckButtonColls();
				DrawRectangleRec(pauseBox, pauseBoxColor);
				DrawTextEx(GetFontDefault(), "PAUSE", { GetScreenWidth() / 2.0f - MeasureTextEx(GetFontDefault(), "PAUSE", 42, 1).x / 2.0f, GetScreenHeight() / 4.0f }, 42, 1,WHITE);

				for (int i = 0; i < 2; i++)
				{
					Rectangle buttonSource = { 0.0f, 0.0f, static_cast<float>(pauseButtons[i].sprite->width), static_cast<float>(pauseButtons[i].sprite->height) };
					Rectangle buttonDestination = { pauseButtons[i].body.x + pauseButtons[i].body.width / 2, pauseButtons[i].body.y + pauseButtons[i].body.height / 2, pauseButtons[i].body.width , pauseButtons[i].body.height };
					Vector2 buttonOrigin = { buttonDestination.width / 2.0f, buttonDestination.height / 2.0f };

					DrawTexturePro(*pauseButtons[i].sprite, buttonSource, buttonDestination, buttonOrigin, 0.0f, pauseButtons[i].color);

					DrawTextEx(GetFontDefault(), pauseButtons[i].text, { pauseButtons[i].body.x + pauseButtons[i].body.width / 2 - MeasureTextEx(GetFontDefault(), pauseButtons[i].text, pauseButtons[i].fontSize, 1).x / 2, pauseButtons[i].body.y + pauseButtons[i].body.height / 2 - MeasureTextEx(GetFontDefault(), pauseButtons[i].text, pauseButtons[i].fontSize, 1).y / 2 }, pauseButtons[i].fontSize, 1,BLACK);
				}

				EndDrawing();
			}
			if (gameState == GameState::Lost)
			{
				const char* lostText = "YOU DIED";
				Vector2 lostTextMeasured = MeasureTextEx(GetFontDefault(), lostText, 72, 1);
				Vector2 lostTextPosition = { GetScreenWidth() / 2 - lostTextMeasured.x / 2, GetScreenHeight() / 8.0f };
				Color pauseBoxColor = { 255,0,0,255 };

				BeginDrawing();
				DrawBackground();
				DrawGround();
				player.Draw();
				for (int i = 0; i < maxEnemies; i++)
				{
					if (enemies[i].GetIsAlive())
					{
						enemies[i].DrawEnemy();
					}
				}

				Rectangle buttonSource = { 0.0f, 0.0f, static_cast<float>(deathButton.sprite->width), static_cast<float>(deathButton.sprite->height) };
				Rectangle buttonDestination = { deathButton.body.x + deathButton.body.width / 2.0f, deathButton.body.y + deathButton.body.height / 2.0f, deathButton.body.width , deathButton.body.height };
				Vector2 buttonOrigin = { buttonDestination.width / 2.0f, buttonDestination.height / 2.0f };
				DrawTexturePro(*deathButton.sprite, buttonSource, buttonDestination, buttonOrigin, 0.0f, deathButton.color);

				DrawTextEx(GetFontDefault(), deathButton.text, { deathButton.body.x + deathButton.body.width / 2.0f - MeasureTextEx(GetFontDefault(), deathButton.text, deathButton.fontSize, 1).x / 2.0f, deathButton.body.y + deathButton.body.height / 2.0f - MeasureTextEx(GetFontDefault(), deathButton.text, deathButton.fontSize, 1).y / 2.0f }, deathButton.fontSize, 1,BLACK);

				DrawTextEx(GetFontDefault(), lostText, lostTextPosition, 72, 1, pauseBoxColor);
				EndDrawing();

				if (CheckCollisionPointRec(GetMousePosition(), deathButton.body))
				{
					deathButton.color = RED;

					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
					{
						inGame = false;
					}
				}
				else
				{
					deathButton.color = WHITE;
				}
			}

			if (WindowShouldClose())
			{
				inGame = false;
				closeApp = true;
			}
		}
	}

	void RunGame::Init()
	{

		inGame = true;
		player = Player(GetScreenWidth() / 2.0f, 6 * GetScreenHeight() / 9.5f, GetScreenWidth() / 26.0f, GetScreenHeight() / 8.7f, WHITE);
		currSystemStats.maxNumberOfEnemies = 2;
		currSystemStats.spawnRate = 3.0f;
		currSystemStats.currTimeToSpawn = 0.0f;
		score = 0.0f;

		gameState = GameState::Playing;
	}

	void RunGame::CheckButtonColls()
	{
		for (int i = 0; i < 2; i++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), pauseButtons[i].body))
			{
				pauseButtons[i].color = RED;

				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				{
					switch (i)
					{
					case 0:
						gameState = GameState::Playing;
						break;
					case 1:
						inGame = false;
						break;
					default:
						break;
					}
				}
			}
			else
			{
				pauseButtons[i].color = WHITE;
			}
		}
	}

	void SetupEnemies(Enemy enemies[], Texture2D* enemySprite)
	{
		for (int i = 0; i < maxEnemies; i++)
		{
			enemies[i] = Enemy(enemyConfigs::defaultRadius, WHITE, enemySprite);
			enemies[i].SetVelocity({ enemyConfigs::defaultVelocityX, enemyConfigs::defaultVelocityY });
		}

	}

	void RunGame::ManageEnemies()
	{
		int count = 0;
		for (int i = 0; i < maxEnemies; i++)
		{
			if (enemies[i].GetIsAlive())
				count++;
		}

		currSystemStats.numberToSpawn = currSystemStats.maxNumberOfEnemies - count;

		if (currSystemStats.currTimeToSpawn >= currSystemStats.spawnRate && currSystemStats.numberToSpawn > 0)
		{
			currSystemStats.currTimeToSpawn = 0;
			SpawnEnemy();
		}

		currSystemStats.currTimeToSpawn += GetFrameTime();
	}

	void RunGame::SpawnEnemy()
	{
		for (int i = 0; i < maxEnemies; i++)
		{
			if (enemies[i].GetIsAlive() == false)
			{
				enemies[i].SetIsAlive(true);
				enemies[i].SpawnRandPosition();
				enemies[i].SetDirection(Vector2Normalize(Vector2Subtract({ player.GetBody().x + player.GetBody().width / 2, player.GetBody().y + player.GetBody().height / 2 }, enemies[i].GetPosition())));
				enemies[i].SetVelocity({ enemyConfigs::defaultVelocityX, enemyConfigs::defaultVelocityY });
				break;
			}
		}
	}

	void RunGame::TakeInput()
	{
		float speed = 450;
		Rectangle newBody = player.GetBody();

		if (IsKeyDown(KEY_A) && newBody.x > 0)
			newBody.x -= speed * GetFrameTime();
		if (IsKeyDown(KEY_D) && newBody.x + newBody.width < GetScreenWidth())
			newBody.x += speed * GetFrameTime();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			player.ShootGun();
		}

		player.Reposition(newBody.x, newBody.y);
	}

	void RunGame::Update()
	{
		UpdateEnemies();
		player.Update();
		UpdateDifficulty();
		UpdateScore();
	}

	void RunGame::UpdateEnemies()
	{
		for (int i = 0; i < maxEnemies; i++)
		{
			if (enemies[i].GetIsAlive() == true)
			{
				enemies[i].Update(player, score);
				enemies[i].SetVelocity({ currSystemStats.currentEnemyVelocity,currSystemStats.currentEnemyVelocity });
			}
		}
	}

	void RunGame::UpdateDifficulty()
	{
		SystemConstants systemConstants;

		currSystemStats.spawnRate -= systemConstants.spawnRate * GetFrameTime();

		if (currSystemStats.currentEnemyAdderCount >= systemConstants.enemyAdderUnit)
		{
			currSystemStats.maxNumberOfEnemies += systemConstants.enemyAdderUnit;
			currSystemStats.currentEnemyAdderCount -= systemConstants.enemyAdderUnit;
		}

		currSystemStats.currentEnemyAdderCount += systemConstants.spawnRate * GetFrameTime();

		if (currSystemStats.currentEnemyVelocity < systemConstants.enemyVelocityCap)
			currSystemStats.currentEnemyVelocity += systemConstants.enemyVelocityAdder * GetFrameTime();
	}

	void RunGame::UpdateScore()
	{
		score += GetFrameTime();
	}

	void RunGame::CheckGameStateConditions()
	{
		if (player.GetIsAlive() == false)
		{
			gameState = GameState::Lost;
		}
		else if (IsKeyPressed(KEY_ESCAPE))
		{
			if (gameState == GameState::Pause)
				gameState = GameState::Playing;
			else
				gameState = GameState::Pause;
		}
	}

	void RunGame::DrawFrame()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawBackground();
		DrawGround();

		player.Draw();
		DrawText(TextFormat("Score: %8i", static_cast<int>(RAYMATH_H::floor(score))), 0, 50, 48, WHITE);
		for (int i = 0; i < maxEnemies; i++)
		{
			if (enemies[i].GetIsAlive())
			{
				enemies[i].DrawEnemy();
			}
		}

		DrawUI();


		EndDrawing();
	}

	void RunGame::DrawBackground()
	{
		Rectangle spriteSource = { 0.0f,0.0f, static_cast<float>(background1.width), static_cast<float>(background1.height) };
		Rectangle spriteDestination = { GetScreenWidth() / 2.0f,GetScreenHeight() / 3.2f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		DrawTexturePro(background0, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
		DrawTexturePro(background1, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
		DrawTexturePro(background2, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
		DrawTexturePro(background3, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
	}

	void RunGame::DrawGround()
	{
		Rectangle spriteSource = { 0.0f,0.0f, static_cast<float>(ground.width), static_cast<float>(ground.height) };
		Rectangle spriteDestination = { GetScreenWidth() / 2.0f,GetScreenHeight() / 3.4f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) * 1.5f };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		DrawTexturePro(ground, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
	}

	void RunGame::DrawUI()
	{
		DrawTextEx(GetFontDefault(), TextFormat("Bullets: %2i/%2i", player.GetGun()->GetCurrentBulletCount(), player.GetGun()->GetMaxBulletCount()), { 0, GetScreenHeight() / 1.2f }, 46, 1.0f, WHITE);
	}

	void RunGame::AssignButtonSprite(Texture2D* buttonSprite)
	{
		for (int i = 0; i < 2; i++)
		{
			pauseButtons[i].sprite = buttonSprite;
		}
		deathButton.sprite = buttonSprite;
	}
};