#pragma once
#include "Player.h"

namespace kuznickiSystem
{
	class RunGame
	{
	private:
		kuznickiGameObjects::Player player = { 0,0,1,1, WHITE };


	public:
		RunGame();
		~RunGame();

		void Start();
		void Update();

		void TakeInput();
	};
}