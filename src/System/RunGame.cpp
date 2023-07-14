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

		player = Player(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 20, 20, WHITE);
		currSystemStats.numberOfEnemies = 1.0f;
		currSystemStats.spawnRate = 1.0f;

		SetupEnemies(enemies);

		while (true)
		{
			ManageEnemies(enemies);

			TakeInput();

			Update();

			BeginDrawing();
			ClearBackground(BLACK);
			player.Draw();

			for (int i = 0; i < maxEnemies; i++)
			{
				if (enemies[i].GetIsAlive())
					DrawCircleV(enemies[i].GetPosition(), 20, RAYWHITE);
			}

			EndDrawing();
		}
	}

	void SetupEnemies(Enemy enemies[])
	{
		for (int i = 0; i < maxEnemies; i++)
		{
			enemies[0] = Enemy();
			enemies[0].SetIsAlive(false);
			enemies[0].Reposition({ -1.0f, -1.0f });
			enemies[0].SetVelocity({ 400.0f, 400.0f });
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

		if (count < currSystemStats.numberOfEnemies)
		{
			int enemiesNeeded = currSystemStats.numberOfEnemies - count;
		}
	}

	void RunGame::TakeInput()
	{
		float speed = 450;
		Rectangle newBody = player.GetBody();

		if (IsKeyDown(KEY_W) && newBody.y > 0)
			newBody.y -= speed * GetFrameTime();
		if (IsKeyDown(KEY_S) && newBody.y + newBody.height < GetScreenHeight())
			newBody.y += speed * GetFrameTime();
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
		player.Update();

		//Code to make an enemy track player
		//enemies[0].SetDirection(Vector2Normalize(Vector2Subtract({ player.GetBody().x, player.GetBody().y }, enemies[0].GetPosition())));

		enemies[0].SetDirection(Vector2Normalize(Vector2Subtract({ player.GetBody().x, player.GetBody().y }, enemies[0].GetPosition())));

		for (int i = 0; i < maxEnemies; i++)
		{
			if (enemies[i].GetIsAlive())
			{
				enemies[i].Update(player);
			}
		}
	}
};