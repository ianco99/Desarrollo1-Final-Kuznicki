#pragma once
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Button.h"

namespace kuznickiSystem
{
	const int maxEnemies = 1500;

	enum class GameState
	{
		Playing,
		Pause,
		Lost
	};

	struct enemyConfigs
	{
		static const int defaultVelocityX = 250;
		static const int defaultVelocityY = 250;

		static const int defaultRadius = 20;
	};

	struct SystemStats
	{
		int maxNumberOfEnemies = 0;
		float currentEnemyAdderCount = 0;
		float currentEnemyVelocity = enemyConfigs::defaultVelocityX;

		int numberToSpawn = 0;
		float currTimeToSpawn = 0;
		float spawnRate = 0; //Time in seconds
	};

	struct SystemConstants
	{
		const float spawnRate = 0.05f;
		const float enemyVelocityAdder = 0.18f;
		const float enemyVelocityCap = 600.0f;
		int enemyAdderUnit = 1;
	};

	class RunGame
	{
	private:
		kuznickiGameObjects::Enemy enemies[maxEnemies];
		kuznickiGameObjects::Player player = { 0,0,1,1, WHITE };
		SystemStats currSystemStats;

		GameState gameState;

		Button deathButton;
		Button pauseButtons[2];
		Rectangle pauseBox;

		float score;
		bool inGame = true;

		Texture2D ground;

		Texture2D background0;
		Texture2D background1;
		Texture2D background2;
		Texture2D background3;
		Texture2D enemySprite;

	public:
		RunGame();
		~RunGame();

		void LoadTextures();
		void LoadButtons();

		void Start(bool& closeApp, Music mainMusic);
		void Init();

		void GameLoop(bool& closeApp, Music mainMusic);

		void Update();
		void UpdateEnemies();
		void UpdateDifficulty();
		void UpdateScore();
		void CheckGameStateConditions();
		void CheckButtonColls(); 

		void DrawFrame();
		void DrawBackground();
		void DrawGround();
		void DrawUI();

		void DrawPause();
		void DrawLoseScreen();

		void ManageEnemies();
		void SpawnEnemy();
		void TakeInput();

		void AssignButtonSprite(Texture2D* buttonSprite);
	};
}