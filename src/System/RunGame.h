#pragma once
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

		int numberToSpawn;
		float currTimeToSpawn = 0;
		float spawnRate; //Time in seconds
	};

	struct SystemConstants
	{
		const float spawnRateConstant = 0.05f;
		int enemyAdderUnit = 1;
	};

	class RunGame
	{
	private:
		kuznickiGameObjects::Enemy enemies[maxEnemies];
		kuznickiGameObjects::Player player = { 0,0,1,1, WHITE };
		SystemStats currSystemStats;

		float score;
		bool playing;
	public:
		RunGame();
		~RunGame();

		void Start();
		void Update();
		void UpdateEnemies();
		void UpdateDifficulty();
		void UpdateScore();
		void CheckWinConditions();

		void ManageEnemies();
		void SpawnEnemy();
		void TakeInput();
	};
}