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
			bullets[i].SetIsAlive(false);
		}

		this->myPlayer = myPlayer;
		canShoot = true;
	}

	Gun::~Gun()
	{

	}

	void Gun::Update()
	{
		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].GetIsAlive())
				bullets[i].Move();
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
		//canShoot = false;

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
				bullets[i].SetIsAlive(true);
				break;
				std::cout << "GODDD";
			}
		}
	}

	Vector2 Gun::GetBulletDirection()
	{
		Vector2 mousePos = GetMousePosition();
		Vector2 distance = Vector2Subtract(mousePos, { myPlayer->x , myPlayer->y });

		return distance;
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

	Bullet Gun::GetBulletByIndex(int index)
	{
		return bullets[index];
	}

	int Gun::GetMaxBullets()
	{
		return maxBullets;
	}

	void Gun::Draw()
	{

		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].GetIsAlive())
			{
				Rectangle spriteSource = { 0.0f,0.0f, static_cast<float>(bullets[i].GetBody().width), static_cast<float>(bullets[i].GetBody().height) };
				Rectangle spriteDestination = { bullets[i].GetBody().x, bullets[i].GetBody().y, bullets[i].GetBody().width, bullets[i].GetBody().height };
				Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

				DrawRectanglePro(bullets[i].GetBody(), spriteOrigin, bullets[i].GetAngle(), bullets[i].GetColor());
			}
		}
	}
}