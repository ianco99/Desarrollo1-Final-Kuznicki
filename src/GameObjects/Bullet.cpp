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

	Bullet::Bullet()
	{

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
		this->velocity = velocity;
	}

	void Bullet::ChangePosition(Vector2 newPosition)
	{
		this->body.x = newPosition.x;
		this->body.y = newPosition.y;
	}

	void Bullet::Move()
	{
		
		this->body.x += direction.x * velocity.x * GetFrameTime();
		this->body.y += direction.y * velocity.y * GetFrameTime();
	}

	void Bullet::RecieveDamage(int damage)
	{

	}

	void Bullet::SetColor(Color color)
	{

	}
	
	void Bullet::SetBody(Rectangle newBody)
	{
		this->body = newBody;
	}

	void Bullet::SetAngle(float newAngle)
	{
		this->angle = newAngle;
	}

	float Bullet::GetAngle()
	{
		return this->angle;
	}

	Rectangle Bullet::GetBody()
	{
		return this->body;
	}

	Color Bullet::GetColor()
	{
		return this->color;
	}
}
