#pragma once
#include "raylib.h"

namespace kuznickiGameObjects
{
	class Bullet
	{
	private:
		Rectangle body = { 0,0,0,0 };
		
		Vector2 velocity;	//Only positive values
		Vector2 acceleration;	//In case I need the bullet to speed up overtime
		Vector2 direction;

		Color color;

		int health;

		bool isAlive = false;

	public:
		Bullet(float sizeX, float sizeY, int health, Color color);
		~Bullet();

		void ChangeDirection(Vector2 direction);
		void ChangeVelocity(Vector2 velocity);

		void RecieveDamage(int damage);

		void ChangeColor(Color color);
	};


}