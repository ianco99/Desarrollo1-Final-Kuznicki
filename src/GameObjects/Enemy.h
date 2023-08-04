#pragma once
#include "raylib.h"
#include "Player.h"

namespace kuznickiGameObjects
{
	class Enemy
	{
	private:
		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;
		Vector2 direction;
		float radius;

		Color color;

		Texture2D* sprite;

		int damage = 1;

		float scoreToGive;
		bool isAlive;

	public:
		Enemy();
		Enemy(float radius, Color color, Texture2D* sprite);
		~Enemy();

		void Update(Player& player, float& score);

		void Move();
		void CheckPlayerCollision(Player& player);
		void CheckBulletCollisions(Gun* currGun, int bulletsSize, float& score);
		bool CheckCollisions(Bullet& bullets);
		void CheckOutOfBounds();

		void SpawnRandPosition();

		void Reposition(Vector2 newPos);
		Vector2 GetPosition();
		void SetVelocity(Vector2 newVelocity);
		Vector2 GetVelocity();

		void SetAcceleration(Vector2 newAcceleration);
		Vector2 GetAcceleration();

		void SetDirection(Vector2 direction);
		Vector2 GetDirection();

		Color GetColor();

		void SetIsAlive(bool value);
		bool GetIsAlive();

		float GetRadius();
		void SetRadius(float newRadius);

		void DrawEnemy();
	};
}