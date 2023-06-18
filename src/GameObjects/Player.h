#pragma once
#include "raylib.h"

#include "Gun.h"

namespace kuznickiGameObjects
{
	class Player
	{
	private:
		Rectangle* body;
		Color color;
		Gun gun = Gun(body);


	public:
		Player(float posX, float posY, float sizeX, float sizeY, Color givenColor);
		~Player();

		void Update();

		void Reposition(float newX, float newY);

		Gun GetGun();
		void ShootGun();

		void Draw();

		Rectangle GetBody();
	};

}