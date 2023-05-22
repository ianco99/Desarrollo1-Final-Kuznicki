#pragma once
#include "raylib.h"

namespace kuznickiGameObjects
{
	class Player
	{
	private:
		Rectangle body;
		Color color;

	public:
		Player(float posX, float posY, float sizeX, float sizeY, Color givenColor);
		~Player();

		void Draw();
	};

}