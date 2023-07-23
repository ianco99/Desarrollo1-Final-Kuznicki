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
		static const int defaultVelocityX = 150;
		static const int defaultVelocityY = 150;

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

	struct ArtAssetsPath
	{
		const char background0[256] = "parallax-demon-woods-bg.png";
		const char background1[256] = "parallax-demon-woods-far-trees.png";
		const char background2[256] = "parallax-demon-woods-mid-trees.png";
		const char background3[256] = "parallax-demon-woods-close-trees.png";
	};

	class RunGame
	{
	private:
		kuznickiGameObjects::Enemy enemies[maxEnemies];
		kuznickiGameObjects::Player player = { 0,0,1,1, WHITE };
		SystemStats currSystemStats;

		float score;
		bool playing = true;

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

		void ManageEnemies();
		void SpawnEnemy();
		void TakeInput();
	};
}