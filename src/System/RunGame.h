#pragma once
#include "Player.h"
#include <Enemy.h>
//#include "Menu.h"

namespace kuznickiSystem
{
	const int maxEnemies = 1500;

	class RunGame
	{
	private:
		kuznickiGameObjects::Player player = { 0,0,1,1, WHITE };
		kuznickiGameObjects::Enemy enemies[maxEnemies];

	public:
		RunGame();
		~RunGame();

		void Start();
		void Update();

		void TakeInput();
	};
}