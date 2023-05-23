#pragma once
#include "raylib.h"

namespace kuznickiGameObjects
{
	class Bullet
	{
	private:
		Rectangle body;
		Vector2 velocity;
		Vector2 acceleration;	//In case I need the bullet to speed up overtime
		Vector2 direction;

	public:
		Bullet();
		~Bullet();
	};

	Bullet::Bullet()
	{
	}

	Bullet::~Bullet()
	{
	}
}