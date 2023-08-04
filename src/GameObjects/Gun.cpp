#include "Gun.h"
#include <iostream>
#include "raymath.h"

namespace kuznickiGameObjects
{
	Gun::Gun(Rectangle& myNewPlayer)
	{
		for (int i = 0; i < maxBullets; i++)
		{
			bullets[i] = Bullet(8.0f, 1, RED);
			bullets[i].SetIsAlive(false);
		}
		this->angle = 0.0f;
		this->myPlayer = &myNewPlayer;
		this->position = { myPlayer->x, myPlayer->y };
		this->canShoot = true;

		this->currentBullets = 1;
		this->maxBulletCount = 1;

		this->sprite = LoadTexture("../rsc/gun.png");

	}

	Gun::~Gun()
	{

	}

	void Gun::Update(Rectangle newPlayer)
	{
		std::cout << position.x;
		position = { newPlayer.x + newPlayer.width + sprite.width * 3.8f, newPlayer.y + newPlayer.height / 2.0f + sprite.height * 3.5f };
		PointGun();
		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].GetIsAlive())
			{
				bullets[i].Move();
				bullets[i].CheckOutOfBounds();
			}
		}
	}

	void Gun::PointGun()
	{
		Vector2 pointTo = GetMousePosition();

		Vector2 playerPos = { position.x , position.y };

		Vector2 distance = { pointTo.x - playerPos.x, pointTo.y - playerPos.y };

		double currAngle = atan(distance.y / distance.x);

		currAngle = currAngle * 180 / PI;

		if (distance.x > 0 && distance.y < 0) //Quad 4
		{
			currAngle += 360;
		}
		else if (distance.x < 0 && distance.y < 0) //Quad 3
		{
			currAngle += 180;
		}
		else if (distance.x < 0 && distance.y > 0) //Quad 2
		{
			currAngle += 180;
		}

		this->angle = static_cast<float>(currAngle);
	}

	void Gun::ToggleCanShoot(bool value)
	{
		canShoot = value;
	}

	void Gun::PullTrigger(Rectangle playerBody)
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
				Shoot(playerBody);
				currentBullets++;
			}
		}
	}

	void Gun::Shoot(Rectangle playerBody)
	{
		Vector2 direction = GetBulletDirection(playerBody);

		float rotationAngle = GetBulletRotation(direction);

		for (int i = 0; i < maxBullets; i++)
		{
			if (!bullets[i].GetIsAlive())
			{
				bullets[i].SetAngle(rotationAngle);
				bullets[i].ChangeDirection(Vector2Normalize(direction));
				bullets[i].ChangeVelocity({ 550,550 });
				bullets[i].ChangePosition({ playerBody.x + playerBody.width + sprite.width,playerBody.y + playerBody.height / 2.0f });
				bullets[i].SetIsAlive(true);
				break;
			}
		}
	}

	Vector2 Gun::GetBulletDirection(Rectangle playerBody)
	{
		Vector2 mousePos = GetMousePosition();
		Vector2 distance = Vector2Subtract(mousePos, { playerBody.x + playerBody.width + sprite.width,playerBody.y + playerBody.height / 2.0f });

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

	int Gun::GetMaxBulletCount()
	{
		return maxBulletCount;
	}

	int Gun::GetCurrentBulletCount()
	{
		int bulletCount = maxBulletCount;
		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].GetIsAlive() == true)
				bulletCount--;
		}

		return bulletCount;
	}

	Vector2 Gun::GetPosition()
	{
		return{ myPlayer->x + myPlayer->width + sprite.width, myPlayer->y + myPlayer->height / 2.0f};
	}

	void Gun::Draw(Rectangle playerBody)
	{
		Rectangle spriteSource = { 0.0f,0.0f, static_cast<float>(sprite.width), static_cast<float>(sprite.height) };
		Rectangle spriteDestination = { playerBody.x + playerBody.width, playerBody.y + playerBody.height / 2, sprite.width * 3.8f, sprite.height * 3.5f };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		DrawTexturePro(sprite, spriteSource, spriteDestination, spriteOrigin, angle, WHITE);

		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].GetIsAlive() == true)
			{
				DrawCircleV(bullets[i].GetPosition(), bullets[i].GetRadius(), bullets[i].GetColor());
			}
		}

		DrawLineEx({ playerBody.x + playerBody.width + sprite.width,playerBody.y + playerBody.height / 2.0f }, { static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) }, 1.0f, RED);

	}
}