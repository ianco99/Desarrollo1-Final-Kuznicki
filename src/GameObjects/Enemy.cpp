#include <iostream>

#include "Enemy.h"

namespace kuznickiGameObjects
{
	Enemy::Enemy(float radius, Color color)
	{
		this->radius = radius;
		this->position = { -1.0f, -1.0f };
		this->color = color;
		this->isAlive = false;
	}

	Enemy::Enemy()
	{

	}

	Enemy::~Enemy()
	{

	}

	void Enemy::Update(Player& player)
	{
		if (isAlive)
		{
			Gun* currGun = player.GetGun();
			int maxBullets = currGun->GetMaxBullets();

			Move();

			for (int i = 0; i < maxBullets; i++)
			{
				if (currGun->GetBulletByIndex(i)->GetIsAlive() == true)
					CheckCollisions(*currGun->GetBulletByIndex(i));
			}
		}
	}

	void Enemy::Move()
	{
		this->position.x += direction.x * velocity.x * GetFrameTime();
		this->position.y += direction.y * velocity.y * GetFrameTime();
	}

	void Enemy::CheckCollisions(Bullet& bullet)
	{
		if (CheckCollisionCircles(position, radius, bullet.GetPosition(), bullet.GetRadius()))
		{
			isAlive = false;
			bullet.SetIsAlive(false);

			if (bullet.GetIsAlive() == false)
				std::cout << bullet.GetIsAlive();
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

	Color Enemy::GetColor()
	{
		return color;
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