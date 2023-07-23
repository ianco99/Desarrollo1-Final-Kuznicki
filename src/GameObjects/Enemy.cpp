#include <iostream>
#include "Enemy.h"

namespace kuznickiGameObjects
{
	enum class SpawnSites { Left, Right, Top };

	Enemy::Enemy(float radius, Color color)
	{
		this->radius = radius;
		this->position = { -1.0f, -1.0f };
		this->color = color;
		this->isAlive = false;
		this->scoreToGive = 5.0f;
	}

	Enemy::Enemy()
	{

	}

	Enemy::~Enemy()
	{

	}

	void Enemy::Update(Player& player, float& score)
	{
		if (isAlive)
		{
			Gun* currGun = player.GetGun();
			int maxBullets = currGun->GetMaxBullets();

			Move();

			for (int i = 0; i < maxBullets; i++)
			{
				if (currGun->GetBulletByIndex(i)->GetIsAlive() == true)
				{
					if (CheckCollisions(*currGun->GetBulletByIndex(i)))
					{
						Bullet* bullet = currGun->GetBulletByIndex(i);
						bullet->SetIsAlive(false);
						this->isAlive = false;

						score += scoreToGive;
					}
				}
			}
		}
	}

	void Enemy::Move()
	{
		this->position.x += direction.x * velocity.x * GetFrameTime();
		this->position.y += direction.y * velocity.y * GetFrameTime();
	}

	bool Enemy::CheckCollisions(Bullet& bullet)
	{
		if (CheckCollisionCircles(position, radius, bullet.GetPosition(), bullet.GetRadius()))
		{
			return true;
			
		}
		return false;
	}

	void Enemy::SpawnRandPosition()
	{
		SpawnSites sites = (SpawnSites)(rand() % 3);
		Vector2 spawnPos;

		switch (sites)
		{
		case kuznickiGameObjects::SpawnSites::Left:
			spawnPos.x = -10;
			spawnPos.y = rand() % GetScreenHeight() / 3;
			break;
		case kuznickiGameObjects::SpawnSites::Right:
			spawnPos.x = GetScreenWidth() + 10;
			spawnPos.y = rand() % GetScreenHeight() / 3;
			break;
		case kuznickiGameObjects::SpawnSites::Top:
			spawnPos.x = rand() % GetScreenWidth();
			spawnPos.y = -10;
			break;
		default:
			spawnPos.x = -10;
			spawnPos.y = -10;
			break;
		}

		Reposition(spawnPos);
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