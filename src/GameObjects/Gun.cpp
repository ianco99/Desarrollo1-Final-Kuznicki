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
		else
		{
			Shoot();
		}
	}

	void Gun::Shoot()
	{
		canShoot = false;

		Vector2 mousePos = GetMousePosition();
		Vector2 distance = Vector2Subtract(mousePos,{ myPlayer->x , myPlayer->y });
					
		float rotationAngle = atan(distance.y/distance.x);
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

		bullets[0].ChangeDirection(Vector2Normalize(distance));
		bullets[0].ChangeVelocity({ 500,500 });
		bullets[0].ChangePosition({ myPlayer->x,myPlayer->y});
		std::cout << "GODDD";

		/*bullets[0].x = myPlayer->x + myPlayer->width / 2;
		bullets[0].y = myPlayer->y + myPlayer->height / 2;*/
	}

	void Gun::Draw()
	{
		if (!canShoot)
			DrawRectangleRec(bullets[0].GetBody(), bullets[0].GetColor());
	}
}