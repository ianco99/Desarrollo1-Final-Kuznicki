#pragma once
#include "Player.h"
#include <Enemy.h>
//#include "Menu.h"

namespace kuznickiSystem
{
	const int maxEnemies = 1500;

	struct SystemStats
	{
		int numberOfEnemies;
		int numberToSpawn;
		float currTimeToSpawn = 0;
		float spawnRate; //Time in seconds
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

		void ManageEnemies();
		void SpawnEnemy();
		void TakeInput();
	};
}