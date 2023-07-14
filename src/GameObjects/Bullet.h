#pragma once
#include "raylib.h"

namespace kuznickiGameObjects
{
	class Bullet
	{
	private:
		float radius;
		float angle;
		Vector2 position;

		Vector2 velocity;	//Only positive values
		Vector2 acceleration;	//In case I need the bullet to speed up overtime
		Vector2 direction;

		Color color;

		int health;

		bool isAlive = false;

	public:
		Bullet(float radius, int health, Color color);
		Bullet();
		~Bullet();

		void ChangeDirection(Vector2 direction);
		void ChangeVelocity(Vector2 velocity);
		void ChangePosition(Vector2 velocity);

		void Move();

		void RecieveDamage(int damage);

		void SetColor(Color color);
		void SetAngle(float newAngle);
		float GetAngle();

		float GetRadius();
		Vector2 GetPosition();
		Color GetColor();
		void SetIsAlive(bool value);
		bool GetIsAlive();
	};


}