#pragma once
#include <iostream>
#include "Player.h"
#include <Enemy.h>
//#include "Menu.h"

namespace kuznickiSystem
{
	const int maxEnemies = 1500;

	struct enemyConfigs
	{
		static const int defaultVelocityX = 250;
		static const int defaultVelocityY = 250;

		static const int defaultRadius = 20;
	};

	struct SystemStats
	{
		int maxNumberOfEnemies;
		float currentEnemyAdderCount;
		float currentEnemyVelocity = enemyConfigs::defaultVelocityX;

		int numberToSpawn;
		float currTimeToSpawn = 0;
		float spawnRate; //Time in seconds
	};

	struct SystemConstants
	{
		const float spawnRate = 0.05f;
		const float enemyVelocityAdder = 0.5f;
		int enemyAdderUnit = 1;
	};

	class RunGame
	{
	private:
		kuznickiGameObjects::Enemy enemies[maxEnemies];
		kuznickiGameObjects::Player player = { 0,0,1,1, WHITE };
		SystemStats currSystemStats;

		float score;
		bool playing = true;

		Texture2D ground;

		Texture2D background0;
		Texture2D background1;
		Texture2D background2;
		Texture2D background3;
	public:
		RunGame();
		~RunGame();

		void LoadTextures();

		void Start();
		void Update();
		void UpdateEnemies();
		void UpdateDifficulty();
		void UpdateScore();
		void CheckWinConditions();

		void DrawFrame();
		void DrawBackground();
		void DrawGround();
		void DrawUI();

		void ManageEnemies();
		void SpawnEnemy();
		void TakeInput();
	};
}