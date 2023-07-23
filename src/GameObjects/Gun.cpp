#include "Gun.h"
#include <iostream>
#include "raymath.h"

namespace kuznickiGameObjects
{
	Gun::Gun(Rectangle* myPlayer)
	{
		for (int i = 0; i < maxBullets; i++)
		{
			bullets[i] = Bullet(8.0f, 1, RED);
			bullets[i].SetIsAlive(false);
		}

		this->myPlayer = myPlayer;
		canShoot = true;

		currentBullets = 1;
		maxBulletCount = 1;

		sprite = LoadTexture("../rsc/gun.png");
	}

	Gun::~Gun()
	{

	}

	void Gun::Update()
	{
		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].GetIsAlive())
			{
				bullets[i].Move();
				bullets[i].CheckOutOfBounds();
			}
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
			float bulletCount = 0;
			for (int i = 0; i < maxBullets; i++)
			{
				if (bullets[i].GetIsAlive() == true)
					bulletCount++;
			}

			if (bulletCount < maxBulletCount)
			{
				Shoot();
				currentBullets++;
			}
		}
	}

	void Gun::Shoot()
	{
		Vector2 direction = GetBulletDirection();

		float rotationAngle = GetBulletRotation(direction);

		for (int i = 0; i < maxBullets; i++)
		{
			if (!bullets[i].GetIsAlive())
			{
				bullets[i].SetAngle(rotationAngle);
				bullets[i].ChangeDirection(Vector2Normalize(direction));
				bullets[i].ChangeVelocity({ 500,500 });
				bullets[i].ChangePosition({ myPlayer->x + myPlayer->width + sprite.width,myPlayer->y + myPlayer->height / 2 });
				bullets[i].SetIsAlive(true);
				break;
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

	Bullet* Gun::GetBulletByIndex(int index)
	{
		Bullet* bullet = &bullets[index];
		return bullet;
	}

	void Gun::DestroyBulletByIndex(int index)
	{
		bullets[index].SetIsAlive(false);
	}

	int Gun::GetMaxBullets()
	{
		return maxBullets;
	}

	void Gun::Draw()
	{
		Rectangle spriteSource = { 0.0f,0.0f, sprite.width, sprite.height };
		Rectangle spriteDestination = { myPlayer->x + myPlayer->width,myPlayer->y + myPlayer->height / 2, sprite.width * 3.8f, sprite.height * 3.5f };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		//DrawRectanglePro(bullets[i].GetRadius(), spriteOrigin, bullets[i].GetAngle(), bullets[i].GetColor());
		DrawTexturePro(sprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);

		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].GetIsAlive() == true)
			{
				//Rectangle spriteSource = { 0.0f,0.0f, static_cast<float>(bullets[i].GetRadius()), static_cast<float>(bullets[i].GetRadius()) };
				//Rectangle spriteDestination = { bullets[i].GetPosition().x, bullets[i].GetPosition().y, bullets[i].GetRadius(), bullets[i].GetRadius() };
				//Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

				DrawCircleV(bullets[i].GetPosition(), bullets[i].GetRadius(), bullets[i].GetColor());
				//DrawRectanglePro(bullets[i].GetRadius(), spriteOrigin, bullets[i].GetAngle(), bullets[i].GetColor());
			}
		}
	}
}