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
		SystemStats currSystemStats;
		kuznickiGameObjects::Player player = { 0,0,1,1, WHITE };
		kuznickiGameObjects::Enemy enemies[maxEnemies];

	public:
		RunGame();
		~RunGame();

		void Start();
		void Update();
		void UpdateEnemies();
		void UpdateDifficulty();

		void ManageEnemies();
		void SpawnEnemy();
		void TakeInput();
	};
}