#pragma once
#include "raylib.h"

namespace kuznickiGameObjects
{
	class Bullet
	{
	private:
		Rectangle body = { 0,0,0,0 };
		float angle;

		Vector2 velocity;	//Only positive values
		Vector2 acceleration;	//In case I need the bullet to speed up overtime
		Vector2 direction;

		Color color;

		int health;

		bool isAlive = false;

	public:
		Bullet(float sizeX, float sizeY, int health, Color color);
		Bullet();
		~Bullet();

		void ChangeDirection(Vector2 direction);
		void ChangeVelocity(Vector2 velocity);
		void ChangePosition(Vector2 velocity);

		void Move();

		void RecieveDamage(int damage);

		void SetColor(Color color);
		void SetBody(Rectangle newBody);
		void SetAngle(float newAngle);
		float GetAngle();

		Rectangle GetBody();
		Color GetColor();
	};


}