#pragma once
#include "raylib.h"

#include "Gun.h"

namespace kuznickiGameObjects
{
	class Player
	{
	private:
		Rectangle body = { 0.0f,0.0f,0.0f, 0.0f };
		Color color;
		Gun gun = Gun(body);

		Texture2D sprite;

		int lives = 3;
		bool isAlive = true;
		bool showingDamage = false;

		float damageColorCurrentTimer = 0.0f;
		float damageColorMaxTimer = 0.5f;

	public:
		Player(float posX, float posY, float sizeX, float sizeY, Color givenColor);
		~Player();

		void Update();

		void Reposition(float newX, float newY);

		Gun* GetGun();
		void ShootGun();

		void Draw();

		Rectangle GetBody();

		void Damage(int damage);
		void StartDamageTimer();

		bool GetIsAlive();
		void SetIsAlive(bool value);
	};

}