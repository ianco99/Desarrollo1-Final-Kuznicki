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

	}

	RunGame::~RunGame()
	{

	}

	void RunGame::Start()
	{
		InitWindow(1024, 768, "MyFinal");

		player = Player(GetScreenWidth() / 2.0f, 6 * GetScreenHeight() / 8.0f, 20, 20, WHITE);
		currSystemStats.numberOfEnemies = 5.0f;
		currSystemStats.spawnRate = 1.0f;

		SetupEnemies(enemies);

		while (true)
		{
			ManageEnemies();

			TakeInput();

			Update();

			BeginDrawing();
			ClearBackground(BLACK);
			player.Draw();

			for (int i = 0; i < maxEnemies; i++)
			{
				if (enemies[i].GetIsAlive())
					DrawCircleV(enemies[i].GetPosition(), enemies[i].GetRadius(), enemies[i].GetColor());
			}

			EndDrawing();
		}
	}

	void SetupEnemies(Enemy enemies[])
	{
		for (int i = 0; i < maxEnemies; i++)
		{
			enemies[i] = Enemy(20.0f, WHITE);
			enemies[i].SetVelocity({ 400.0f, 400.0f });
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

		currSystemStats.numberToSpawn = currSystemStats.numberOfEnemies - count;

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
				enemies[i].Reposition({ -1.0f, -1.0f });
				enemies[i].SetVelocity({ 400.0f, 400.0f });
				break;
			}
		}
	}

	void RunGame::TakeInput()
	{
		float speed = 450;
		Rectangle newBody = player.GetBody();

		/*if (IsKeyDown(KEY_W) && newBody.y > 0)
			newBody.y -= speed * GetFrameTime();*/
		/*if (IsKeyDown(KEY_S) && newBody.y + newBody.height < GetScreenHeight())
			newBody.y += speed * GetFrameTime();*/
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
	}

	void RunGame::UpdateEnemies()
	{
		for (int i = 0; i < maxEnemies; i++)
		{
			if (enemies[i].GetIsAlive() == true)
			{
				enemies[i].Update(player);
				enemies[i].SetDirection(Vector2Normalize(Vector2Subtract({ player.GetBody().x, player.GetBody().y }, enemies[i].GetPosition())));
			}
		}
	}
};