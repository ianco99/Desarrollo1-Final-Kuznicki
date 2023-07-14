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

		int damage;

		bool isAlive;

	public:
		Enemy();
		Enemy(float radius, Color color);
		~Enemy();

		void Update(Player player);

		void Move();
		void CheckCollisions(Bullet bullets);

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
	};
}