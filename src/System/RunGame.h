#pragma once
#include "Player.h"
//#include "Menu.h"

namespace kuznickiSystem
{
	class RunGame
	{
	private:
		kuznickiGameObjects::Player player = { 0,0,1,1, WHITE };
		//Menu gameMenu;

	public:
		RunGame();
		~RunGame();

		void Start();
		void Update();

		void TakeInput();
	};
}