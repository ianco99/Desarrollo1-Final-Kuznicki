#pragma once
#include "Player.h"
#include <Enemy.h>
//#include "Menu.h"

namespace kuznickiSystem
{
	class RunGame
	{
	private:
		kuznickiGameObjects::Player player = { 0,0,1,1, WHITE };
		kuznickiGameObjects::Enemy enemy;

	public:
		RunGame();
		~RunGame();

		void Start();
		void Update();

		void TakeInput();
	};
}