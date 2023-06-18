#include <iostream>

#include "Enemy.h"

namespace kuznickiGameObjects
{
	Enemy::Enemy()
	{

	}

	Enemy::~Enemy()
	{

	}

	void Enemy::Update(Player player)
	{
		if (isAlive)
		{
			int maxBullets = player.GetGun().GetMaxBullets();
			Gun currGun = player.GetGun();

			Move();

			for (int i = 0; i < maxBullets; i++)
			{
				if (currGun.GetBulletByIndex(i).GetIsAlive())
					CheckCollisions(currGun.GetBulletByIndex(i));
			}
		}
	}

	void Enemy::Move()
	{
		std::cout << "esto ocurre?";

		this->position.x += direction.x * velocity.x * GetFrameTime();
		this->position.y += direction.y * velocity.y * GetFrameTime();
	}

	void Enemy::CheckCollisions(Bullet bullet)
	{
		if (CheckCollisionCircleRec(position, radius, bullet.GetBody()))
		{
			std::cout << "que onda";
		}
	}

	void Enemy::Reposition(Vector2 newPos)
	{
		position = newPos;
	}

	Vector2 Enemy::GetPosition()
	{
		return position;
	}

	void Enemy::SetVelocity(Vector2 newVelocity)
	{
		velocity = newVelocity;
	}

	Vector2 Enemy::GetVelocity()
	{
		return velocity;
	}

	void Enemy::SetAcceleration(Vector2 newAcceleration)
	{

	}

	Vector2 Enemy::GetAcceleration()
	{
		return acceleration;
	}

	void Enemy::SetDirection(Vector2 newDirection)
	{
		direction = newDirection;
	}

	Vector2 Enemy::GetDirection()
	{
		return direction;
	}

	bool Enemy::GetIsAlive()
	{
		return isAlive;
	}

	void Enemy::SetIsAlive(bool value)
	{
		isAlive = value;
	}

	float Enemy::GetRadius()
	{
		return radius;
	}

	void Enemy::SetRadius(float newRadius)
	{
		radius = newRadius;
	}
}