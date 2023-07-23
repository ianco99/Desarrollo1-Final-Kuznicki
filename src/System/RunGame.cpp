#include <iostream>

#include "RunGame.h"
#include "raylib.h"
#include "raymath.h"
#include "Player.h"

using namespace kuznickiGameObjects;
namespace kuznickiSystem
{
	void SetupEnemies(Enemy enemies[]);

	RunGame::RunGame()
	{
		score = 0;
	}

	RunGame::~RunGame()
	{

	}

	void RunGame::Start()
	{
		playing = true;
		player = Player(GetScreenWidth() / 2.0f, 6 * GetScreenHeight() / 8.0f, 20, 20, WHITE);
		currSystemStats.maxNumberOfEnemies = 1.0f;
		currSystemStats.spawnRate = 5.0f;

		SetupEnemies(enemies);

		while (playing)
		{
			ManageEnemies();

			TakeInput();

			Update();

			CheckWinConditions();

			BeginDrawing();
			ClearBackground(BLACK);
			player.Draw();
			DrawText(TextFormat("Score: %8i", static_cast<int>(RAYMATH_H::floor(score))), 0, 50, 48, WHITE);
			for (int i = 0; i < maxEnemies; i++)
			{
				if (enemies[i].GetIsAlive())
				{
					DrawCircleV(enemies[i].GetPosition(), enemies[i].GetRadius(), enemies[i].GetColor());
				}
			}

			EndDrawing();
		}
	}

	void SetupEnemies(Enemy enemies[])
	{
		for (int i = 0; i < maxEnemies; i++)
		{
			enemies[i] = Enemy(enemyConfigs::defaultRadius, WHITE);
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
				enemies[i].SetDirection(Vector2Normalize(Vector2Subtract({ player.GetBody().x, player.GetBody().y }, enemies[i].GetPosition())));
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
				//enemies[i].SetDirection(Vector2Normalize(Vector2Subtract({ player.GetBody().x, player.GetBody().y }, enemies[i].GetPosition())));
				enemies[i].Update(player, score);
			}
		}
	}

	void RunGame::UpdateDifficulty()
	{
		SystemConstants systemConstants;

		currSystemStats.spawnRate -= systemConstants.spawnRateConstant * GetFrameTime();

		if (currSystemStats.currentEnemyAdderCount >= systemConstants.enemyAdderUnit)
		{
			currSystemStats.maxNumberOfEnemies += systemConstants.enemyAdderUnit;
			currSystemStats.currentEnemyAdderCount -= systemConstants.enemyAdderUnit;
		}
		currSystemStats.currentEnemyAdderCount += systemConstants.spawnRateConstant * GetFrameTime();
	}

	void RunGame::UpdateScore()
	{
		score += GetFrameTime();
	}

	void RunGame::CheckWinConditions()
	{
		if (player.GetIsAlive() == false)
		{
			playing = false;
		}
	}
};