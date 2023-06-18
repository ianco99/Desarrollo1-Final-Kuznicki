#pragma once
#include "raylib.h"

namespace kuznickiGameObjects
{
	class Enemy
	{
	private:
		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;
		float radius;

		Color color;

		int damage;


	public:
		Enemy();
		~Enemy();

		void Reposition(Vector2 newPos);
		Vector2 GetPosition();
		void SetVelocity(Vector2 newVelocity);
		Vector2 GetVelocity();

		void SetAcceleration(Vector2 newAcceleration);
		Vector2 GetAcceleration();
	};
}