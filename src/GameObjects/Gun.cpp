#include "Gun.h"
#include <iostream>
#include "raymath.h"

namespace kuznickiGameObjects
{
	Gun::Gun(Rectangle* myPlayer)
	{
		for (int i = 0; i < maxBullets; i++)
		{
			bullets[i] = Bullet(20, 20, 1, RED);
		}

		this->myPlayer = myPlayer;
		canShoot = true;
	}

	Gun::~Gun()
	{

	}

	void Gun::Update()
	{
		if (!canShoot)
		{
			//bullets[0].x = 
			bullets[0].Move();
		}
	}

	void Gun::ToggleCanShoot(bool value)
	{
		canShoot = value;
	}

	void Gun::PullTrigger()
	{
		if (canShoot)
		{
			Shoot();
		}
	}

	void Gun::Shoot()
	{
		canShoot = false;

		Vector2 direction = GetBulletDirection();

		float rotationAngle = GetBulletRotation(direction);

		for (int i = 0; i < maxBullets; i++)
		{
			if (!bullets[i].GetIsAlive())
			{
				bullets[i].SetAngle(rotationAngle);
				bullets[i].ChangeDirection(Vector2Normalize(direction));
				bullets[i].ChangeVelocity({ 500,500 });
				bullets[i].ChangePosition({ myPlayer->x,myPlayer->y });
				std::cout << "GODDD";
			}
		}
	}

	Vector2 Gun::GetBulletDirection()
	{
		Vector2 mousePos = GetMousePosition();
		Vector2 distance = Vector2Subtract(mousePos, { myPlayer->x , myPlayer->y });
	}

	float Gun::GetBulletRotation(Vector2 distance)
	{
		float rotationAngle = atan(distance.y / distance.x);
		rotationAngle = rotationAngle * 180 / PI;

		if (distance.x > 0 && distance.y < 0) //Quad 4
		{
			rotationAngle += 360;
		}
		else if (distance.x < 0 && distance.y < 0) //Quad 3
		{
			rotationAngle += 180;
		}
		else if (distance.x < 0 && distance.y > 0) //Quad 2
		{
			rotationAngle += 180;
		}

		return rotationAngle;
	}

	void Gun::Draw()
	{
		//pls mira el asteroids y copia lo de draw texture pro


		Rectangle spriteSource = { 0.0f,0.0f, static_cast<float>(bullets[0].GetBody().width), static_cast<float>(bullets[0].GetBody().height) };
		Rectangle spriteDestination = { bullets[0].GetBody().x, bullets[0].GetBody().y, bullets[0].GetBody().width, bullets[0].GetBody().height };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		if (!canShoot)
			DrawRectanglePro(bullets[0].GetBody(), spriteOrigin, bullets[0].GetAngle(), bullets[0].GetColor());
	}
}