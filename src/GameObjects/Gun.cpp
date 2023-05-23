#include "Gun.h"
#include <iostream>

using namespace kuznickiGameObjects;

Gun::Gun(Rectangle* myPlayer)
{
	for (int i = 0; i < maxBullets; i++)
	{
		bullets[i] = { myPlayer->x,myPlayer->y,5,5 };
	}

	this->myPlayer = myPlayer;
	canShoot = true;
}

Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::Update()
{
	if (!canShoot)
	{
		//bullets[0].x = 
		bullets[0].x += 200 * GetFrameTime();
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
	bullets[0].x = myPlayer->x + myPlayer->width/2;
	bullets[0].y = myPlayer->y + myPlayer->height / 2;
}

void Gun::Draw()
{
	if (!canShoot)
		DrawRectangleRec(bullets[0], RED);
}