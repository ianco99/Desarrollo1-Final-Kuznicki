#include "Bullet.h"

namespace kuznickiGameObjects
{
	Bullet::Bullet(float sizeX, float sizeY, int health, Color color)
	{
		this->body.width = sizeX;
		this->body.height = sizeY;

		this->health = health;
		
		this->color = color;
	}

	Bullet::~Bullet()
	{

	}

	void Bullet::ChangeDirection(Vector2 direction)
	{
		this->direction = direction;
	}

	void Bullet::ChangeVelocity(Vector2 velocity)
	{

	}

	void Bullet::RecieveDamage(int damage)
	{

	}

	void Bullet::ChangeColor(Color color)
	{

	}
}
