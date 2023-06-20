#include <iostream>

#include "RunGame.h"
#include "raylib.h"
#include "raymath.h"
#include "Player.h"

using namespace kuznickiGameObjects;
namespace kuznickiSystem
{
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
		enemies[0] = Enemy();
		enemies[0].SetIsAlive(true);
		enemies[0].Reposition({ -1.0f, -1.0f });
		enemies[0].SetVelocity({ 400.0f, 400.0f });

		while (true)
		{
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