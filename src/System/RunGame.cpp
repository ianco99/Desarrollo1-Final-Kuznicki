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
		LoadTextures();
	}

	RunGame::~RunGame()
	{

	}

	void RunGame::LoadTextures()
	{
		ArtAssetsPath paths;
		ground = LoadTexture("../rsc/ground.png");
		background0 = LoadTexture("../rsc/parallax-demon-woods-bg.png");
		background1 = LoadTexture("../rsc/parallax-demon-woods-far-trees.png");
		background2 = LoadTexture("../rsc/parallax-demon-woods-mid-trees.png");
		background3 = LoadTexture("../rsc/parallax-demon-woods-close-trees.png");
		/*background1 = paths.background1;
		background2 = paths.background2;
		background3 = paths.background3;*/
	}

	void RunGame::Start()
	{
		playing = true;
		player = Player(GetScreenWidth() / 2.0f, 6 * GetScreenHeight() / 9.5f, GetScreenWidth() / 26.0f, GetScreenHeight() / 8.7f, WHITE);
		currSystemStats.maxNumberOfEnemies = 2.0f;
		currSystemStats.spawnRate = 3.0f;	

		SetupEnemies(enemies);

		while (playing)
		{
			ManageEnemies();

			TakeInput();

			Update();

			CheckWinConditions();

			DrawFrame();
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

		if (currSystemStats.currentEnemyVelocity < 600.0f)
			currSystemStats.currentEnemyVelocity += systemConstants.enemyVelocityAdder * GetFrameTime();
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

		DrawLine(player.GetGun()->GetPosition().x, player.GetGun()->GetPosition().y, GetMouseX(), GetMouseY(), RED);

		EndDrawing();
	}

	void RunGame::DrawBackground()
	{
		Rectangle spriteSource = { 0.0f,0.0f, background1.width, background1.height };
		Rectangle spriteDestination = { GetScreenWidth()/2,GetScreenHeight()/3.2f, GetScreenWidth(), GetScreenHeight()};
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		//DrawRectanglePro(bullets[i].GetRadius(), spriteOrigin, bullets[i].GetAngle(), bullets[i].GetColor());
		DrawTexturePro(background0, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
		DrawTexturePro(background1, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
		DrawTexturePro(background2, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
		DrawTexturePro(background3, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
	}

	void RunGame::DrawGround()
	{
		Rectangle spriteSource = { 0.0f,0.0f, ground.width, ground.height };
		Rectangle spriteDestination = { GetScreenWidth() / 2,GetScreenHeight() / 3.4f, GetScreenWidth(), GetScreenHeight() * 1.5f };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		DrawTexturePro(ground, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);
	}

	void RunGame::DrawUI()
	{
		DrawText(TextFormat("Bullets: %2i/%2i", player.GetGun()->GetCurrentBulletCount(),player.GetGun()->GetMaxBulletCount()), 0, GetScreenHeight() / 1.2f, 46, WHITE);
	}
};