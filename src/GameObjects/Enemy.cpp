#include <iostream>
#include "Enemy.h"

namespace kuznickiGameObjects
{
	enum class SpawnSites { Left, Right, Top };

	Enemy::Enemy(float radius, Color color, Texture2D* sprite)
	{
		this->radius = radius;
		this->position = { -1.0f, -1.0f };
		this->color = color;
		this->isAlive = false;
		this->scoreToGive = 5.0f;
		this->acceleration = { 0.0f, 0.0f };
		this->direction = { 0.0f, 0.0f };
		this->velocity = { 0.0f, 0.0f };

		this->sprite = sprite;
	}

	Enemy::Enemy()
	{
		this->position = { 0.0f, 0.0f };
		this->velocity = { 0.0f, 0.0f };
		this->acceleration = { 0.0f, 0.0f };
		this->direction = { 0.0f, 0.0f };
		this->radius = 0.0f;

		this->color = WHITE;
		this->sprite = nullptr;
		this->scoreToGive = 0.0f;
		this->isAlive = false;
	}

	Enemy::~Enemy()
	{

	}

	void Enemy::Update(Player& player, float& score)
	{
		if (isAlive)
		{
			Gun* currGun = player.GetGun();

			Move();

			CheckPlayerCollision(player);

			CheckBulletCollisions(currGun, currGun->GetMaxBullets(), score);

			CheckOutOfBounds();
		}
	}

	void Enemy::CheckBulletCollisions(Gun* currGun, int bulletsSize, float& score)
	{
		for (int i = 0; i < bulletsSize; i++)
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
			player.Damage(damage);
			if (player.GetIsAlive())
			{
				SetIsAlive(false);
			}
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
		float screenMargin = 10.0f;
		int yLimit = static_cast<int>(GetScreenHeight() / 3.0f);
		SpawnSites sites = (SpawnSites)(rand() % 3);
		Vector2 spawnPos;

		switch (sites)
		{
		case kuznickiGameObjects::SpawnSites::Left:
			spawnPos.x = -screenMargin;
			spawnPos.y = static_cast<float>(rand() % yLimit);
			break;
		case kuznickiGameObjects::SpawnSites::Right:
			spawnPos.x = GetScreenWidth() + screenMargin;
			spawnPos.y = static_cast<float>(rand() % yLimit);
			break;
		case kuznickiGameObjects::SpawnSites::Top:
			spawnPos.x = static_cast<float>(rand() % GetScreenWidth());
			spawnPos.y = -screenMargin;
			break;
		default:
			spawnPos.x = -screenMargin;
			spawnPos.y = -screenMargin;
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
		Rectangle spriteSource = { 0.0f,0.0f, static_cast<float>(sprite->width), static_cast<float>(sprite->height) };
		Rectangle spriteDestination = { position.x, position.y, radius * 2.0f, radius * 2.25f };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		DrawTexturePro(*sprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, color);
	}
}