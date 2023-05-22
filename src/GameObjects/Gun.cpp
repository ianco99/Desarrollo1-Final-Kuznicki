#include "Gun.h"
#include "Player.h"
#include <iostream>

using namespace kuznickiGameObjects;

Gun::Gun()
{
	for (int i = 0; i < maxBullets; i++)
	{
		bullets[i] = { 0,0,5,5 };
	}

	//this->myPlayer = player;
	//canShoot = true;
}

Gun::~Gun()
{
}

void Gun::Update()
{
	if (canShoot)
	{
		bullets[0].x = 
		bullets[0].x += 200 * GetFrameTime();
	}
}

void Gun::ToggleCanShoot(bool value)
{
	canShoot = value;
}

void Gun::PullTrigger()
{
	//if (canShoot)
	//{
		Shoot();
	//}
	//else
	//{

	//}
}

void Gun::Shoot()
{
	canShoot = true;
}

void Gun::Draw()
{
	DrawRectangleRec(bullets[0], RED);
}