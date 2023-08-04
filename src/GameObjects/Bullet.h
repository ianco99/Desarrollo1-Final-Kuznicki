#pragma once
#include "raylib.h"

namespace kuznickiGameObjects
{
	class Bullet
	{
	private:
		float radius = 0.0f;
		float angle = 0.0f;
		Vector2 position = { 0.0f, 0.0f };
		
		Vector2 velocity = { 0.0f, 0.0f };	
		Vector2 acceleration = { 0.0f, 0.0f };	
		Vector2 direction = { 0.0f, 0.0f };

		Color color = WHITE;

		int health = 0;

		bool isAlive = false;

	public:
		Bullet(float radius, int health, Color color);
		Bullet();
		~Bullet();

		void ChangeDirection(Vector2 newDirection);
		void ChangeVelocity(Vector2 newVelocity);
		void ChangePosition(Vector2 newPosition);

		void Move();
		void CheckOutOfBounds();

		void RecieveDamage(int damage);

		void SetColor(Color newColor);
		void SetAngle(float newAngle);
		float GetAngle();

		float GetRadius();
		Vector2 GetPosition();
		Color GetColor();
		void SetIsAlive(bool value);
		bool GetIsAlive();
	};


}