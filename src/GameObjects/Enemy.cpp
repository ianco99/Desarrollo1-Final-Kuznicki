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

		sprite = LoadTexture("../rsc/enemy.png");
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

			CheckPlayerCollision(player);

			CheckBulletCollisions(player.GetGun(), player.GetGun()->GetMaxBullets(), score);

			CheckOutOfBounds();
		}
	}

	void Enemy::CheckBulletCollisions(Gun* currGun, int maxBullets, float& score)
	{
		for (int i = 0; i < maxBullets; i++)
		{
			if (currGun->GetBulletByIndex(i)->GetIsAlive() == true)
			{
				if (CheckCollisions(*currGun->GetBulletByIndex(i)))
				{
					currGun->DestroyBulletByIndex(i);

					this->isAlive = false;

					score += scoreToGive;
				}
			}
		}
	}

	void Enemy::CheckPlayerCollision(Player& player)
	{
		if (CheckCollisionCircleRec(position, radius, player.GetBody()))
		{
			player.SetIsAlive(false);
		}
	}

	void Enemy::CheckOutOfBounds()
	{
		if (position.x - radius > GetScreenWidth() + 15 ||
			position.x + radius < 0 - 15 ||
			position.y + radius > GetScreenHeight())
		{
			isAlive = false;
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
		acceleration = newAcceleration;
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

	void Enemy::DrawEnemy()
	{
		Rectangle spriteSource = { 0.0f,0.0f, static_cast<float>(sprite.width), static_cast<float>(sprite.height) };
		Rectangle spriteDestination = { position.x, position.y, radius * 2.0f, radius * 2.25f };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		DrawTexturePro(sprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, color);
	}
}