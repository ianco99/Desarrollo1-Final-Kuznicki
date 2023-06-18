#include "Enemy.h"

namespace kuznickiGameObjects
{
	Enemy::Enemy()
	{

	}

	Enemy::~Enemy()
	{

	}

	void Enemy::Update()
	{

	}

	void Enemy::Reposition(Vector2 newPos)
	{

	}

	Vector2 Enemy::GetPosition()
	{
		return position;
	}

	void Enemy::SetVelocity(Vector2 newVelocity)
	{

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

	bool Enemy::GetIsAlive()
	{
		return isAlive;
	}

	void Enemy::SetIsAlive(bool value)
	{
		isAlive = value;
	}
}