#include "Bullet.h"

namespace kuznickiGameObjects
{
	Bullet::Bullet(float radius, int health, Color color)
	{
		this->radius = radius;

		this->health = health;
		
		this->color = color;
	}

	Bullet::Bullet()
	{

	}
	
	Bullet::~Bullet()
	{

	}

	void Bullet::ChangeDirection(Vector2 newDirection)
	{
		this->direction = newDirection;
	}

	void Bullet::ChangeVelocity(Vector2 newVelocity)
	{
		this->velocity = newVelocity;
	}

	void Bullet::ChangePosition(Vector2 newPosition)
	{
		this->position.x = newPosition.x;
		this->position.y = newPosition.y;
	}

	void Bullet::Move()
	{
		
		this->position.x += direction.x * velocity.x * GetFrameTime();
		this->position.y += direction.y * velocity.y * GetFrameTime();
	}

	void Bullet::CheckOutOfBounds()
	{
		if (position.x - radius > GetScreenWidth() + 15 ||
			position.x + radius < 0 - 15 ||
			position.y + radius > GetScreenHeight() ||
			position.y + radius < 0)
		{
			isAlive = false;
		}
	}

	void Bullet::RecieveDamage(int damage)
	{
		health -= damage;
	}

	void Bullet::SetColor(Color newColor)
	{
		this->color = newColor;
	}

	void Bullet::SetAngle(float newAngle)
	{
		this->angle = newAngle;
	}

	float Bullet::GetAngle()
	{
		return this->angle;
	}

	float Bullet::GetRadius()
	{
		return this->radius;
	}

	Vector2 Bullet::GetPosition()
	{
		return this->position;
	}

	Color Bullet::GetColor()
	{
		return this->color;
	}

	void Bullet::SetIsAlive(bool value)
	{
		isAlive = value;
	}

	bool Bullet::GetIsAlive()
	{
		return isAlive;
	}
}
